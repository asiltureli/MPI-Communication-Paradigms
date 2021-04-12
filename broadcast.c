#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* Replicate Data from root process to
/* other processes in comm
*/
void MPI_Broadcast(int ∗data , 
                  int count , 
                  MPI_TYPE datatype , 
                  int root ,
                  MPI_Comm comm
                  )
{
    int comm_size, rank;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    /* Root sends all */
    if(rank == root)
    {
        /* Send to all */
        for(int i = 0; i < comm_size; i++)
        {
            if(i != root)
            {
                MPI_Send(data,
                        1,
                        datatype,
                        i,
                        11,
                        comm
                        );
            }
        }
    }
    /* Others receive */
    else
    {
        MPI_Recv(data,
                1,
                datatype,
                root,
                11,
                MPI_STATUS_IGNORE
                );
    }
}
#endif