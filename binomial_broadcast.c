#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* @brief 
/* Broadcast data in a binomial manner
/*
*/
void binomial_broadcast(int* buffer, 
                        int count, 
                        MPI_Datatype datatype, 
                        int root, 
                        MPI_Comm comm
                        )
{
    int my_rank, num_ranks;
    MPI_Comm_rank(comm, &my_rank);
    MPI_Comm_size(comm, &num_ranks);

    int tag         = 0;
    int interval_ub = num_ranks;
    int distance    = interval_ub / 2;

    int sender = 0;
    int phase  = 0;
    int shifted_rank = (my_rank - root + num_ranks) % num_ranks;

    while (distance > 0)
    {
        int dest = sender + (interval_ub - sender) / 2 ;
        int shifted_dest = (dest + root) % num_ranks;
        int shifted_sender = (sender + root) % num_ranks;
        // Send data from shifted sender
        if (my_rank == shifted_sender) {
            MPI_Send(buffer, 
                     count,
                     datatype, 
                     shifted_dest, 
                     tag, 
                     comm
                     );
        }
        // Receive data at shifted receiver
        else if (my_rank == shifted_dest)
        {
            MPI_Recv(buffer, 
                     count, 
                     datatype, 
                     shifted_sender, 
                     tag, 
                     comm, 
                     MPI_STATUS_IGNORE
                     );
        }

        if (dest <= shifted_rank)
            sender = dest;

        if (dest > shifted_rank)
            interval_ub = dest;

        distance = (interval_ub - sender) / 2;
    }
}
#endif