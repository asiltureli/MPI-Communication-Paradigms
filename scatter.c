#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* @brief 
/* Distribute chunks of data from root
/* to other processes in comm
/*
/* @details 
/* Requirements:
/*
/* 1) sbuf should be large enough to provide scount*nprocs elements
/* 2) rbuf should be large enough to accommodate scount elements
*/
void MPI_Scatter(int ∗sbuf , 
                int scount , 
                MPI_TYPE sdatatype,
                int *rbuf,
                int rcount, 
                int root,
                MPI_TYPE rdatatype,
                MPI_Comm comm
                )
{
    int comm_size, rank;
    MPI_Comm_size(comm, &comm_size);
    MPI_Comm_rank(comm, &rank);
    /* Root scatters all */
    if(rank == root)
    {
        /* Send to all */
        for(int i = 0; i < comm_size; i++)
        {
            MPI_Send(sbuf + i*scount*extent(sdatatype),
                    scount,
                    datatype,
                    i,
                    11,
                    comm
                    );
        }
    }
    /* Others receive */
    else
    {
        MPI_Recv(rbuf,
                rcount,
                rdatatype,
                root,
                11,
                MPI_STATUS_IGNORE
                );
    }
}
#endif