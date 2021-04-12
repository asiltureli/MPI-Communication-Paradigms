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
/* apply summation and save in 
/* root rank
*/
void MPI_Reduce_sum(int *sendbuf , 
                    int *recvbuf ,
                    int root, 
                    MPI_Comm comm
                    )
{
    int size, rank;
    MPI_Comm_size(comm , &size);
    MPI_Comm_rank(comm , &rank);
    int MPI_Send(sendbuf, 
                1,         
                MPI_INT, 
                root,
                23, 
                comm
                );
    if(rank == root)
    {
        int temp;
        *recvbuf = 0;
        for(int i = 1; i < 4; i++)
        {
            int MPI_Recv(&temp, 
                        1, 
                        MPI_INT, 
                        i, 
                        23, 
                        comm, 
                        MPI_STATUS_IGNORE
                        );
                    }
            *recvbuf += temp;
    }
}
#endif