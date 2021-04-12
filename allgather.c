#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* @brief 
/* Gather chunks of data from all process
/* in comm to all processes
/*
/* @details 
/* No root ranks - all ranks receive a copy of the gathered data
/* - Data chunks are stored in increasing order of sender's ranks
/* - Each rank also receives one data chunk from itself
/* - sbuf must be large enough to provide scount elements
/* - rbuf must be large enough to accommodate rcount*nprocs elements
/* - Type signatures must match across all ranks
/*
/*          Simply MPI_Gather + MPI_Bcast
/*
*/
void MPI_Allgather(int *sbuf,
                   int scount,
                   MPI_TYPE sdtype,
                   int *rbuf,
                   int rcount,
                   MPI_TYPE rdtype,
                   MPI_Comm comm
                   )
{
    int rank, comm_size;
    MPI_Comm_size(comm, &comm_size);
    MPI_Comm_rank(comm, &rank);
    /* ---------- Firstly gather --------------- */

    MPI_send(sbuf + scount*extent(sdtype),
            scount,
            sdtype,
            rbuf,
            99,
            comm
            );

    for(int i = 0; i < comm_size; i++)
    {
        MPI_recv(rbuf + i*rcount*extent(rdtype),
                rcount,
                rdtype,
                sbuf,
                99,
                comm,
                MPI_STATUS_IGNORE
                );
    }


    /* ---------- Secondly Bcast --------------- */
    for(i = 0; i < comm_size; i++)
    {
        MPI_send(sbuf,
                scount,
                sdtype,
                rbuf,
                99
                comm,
                );
    }

    for(i = 0; i < comm_size; i++)
    {
        MPI_recv(rbuf,
                rcount,
                rdtype,
                sbuf,
                99
                comm,
                MPI_STATUS_IGNORE
                );
    }
}

#endif