#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* @brief 
/* Gather chunks of data from child processes
/* to root process in comm
/*
/* @details 
/* Requirements:
/*
/* 1) sbuf must be large enough to provide scount elements
/* 2) rbuf must be large enough to accommodate rcount*nprocs elements
/*
*/
void MPI_Gather(int ∗sbuf, 
                int scount, 
                MPI_TYPE sdatatype,
                int *rbuf,
                int rcount, 
                int root,
                MPI_TYPE rdatatype,
                MPI_Comm comm
                )
{
    int comm_size, rank;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    /* Others send */
    MPI_Send(sbuf,
            scount,
            sdatatype,
            root,
            11,
            MPI_STATUS_IGNORE
            );
    /* Root gathers all */
    if(rank == root)
    {
        /* Receive from all */
        for(int i = 0; i < comm_size; i++)
        {
            MPI_Recv(rbuf + i*rcount*extent(rdatatype),
                    rcount,
                    datatype,
                    i,
                    11,
                    comm
                    );
        }
    }
}
#endif