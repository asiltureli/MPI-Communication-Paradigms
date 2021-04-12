#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
/* @brief 
/*
/* Gather data from all ranks 
/* apply multiplication and 
/* save in root rank
*/
void MPI_Reduce_product(int *sendbuf , 
                        int *recvbuf ,
                        int root, 
                        MPI_Comm comm
                        )
{
    int rank, size, temp;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    MPI_send(sendbuf,
            1,
            MPI_INT,
            root,
            99,
            comm
            );
    if(rank == root)
    {
        *recvbuf = 1;
        for(int i = 0; i < size; i++)
        {
            MPI_recv(&temp,
                    1,
                    MPI_INT,
                    i,
                    99,
                    comm,
                    MPI_STATUS_IGNORE
                    );
            result *= temp;
        }
    }
}
#endif