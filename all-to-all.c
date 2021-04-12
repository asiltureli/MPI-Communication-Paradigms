#if defined _OPENMP
#include <omp.h>
#elif defined MPI_INT
#include <mpi.h>
#elif defined WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* @brief 
/* Perform an all-to-all scatter/gather with
/* all processes in comm
/*
/* @details 
/* Each rank distributes its sendbuf to every rank in the communicator 
/* (including itself)

/* - Data chunks are read in increasing order of the receiver’s rank
/* - Data chunks are stored in increasing order of the sender’s rank
/* - sbuf must be large enough to provide scount*nprocs elements
/* - rbuf must be large enough to accommodate rcount*nprocs elements
/*
/*          Simply multiple MPI_Scatter + MPI_Gather
/*
*/

int MPI_all_to_all(int *sendbuf, int count, int *recvbuf, MPI_Comm comm) {
    // Initialization
    int size, rank;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    // Communication
    for (int i = 0; i < size; ++i) {
      int MPI_Sendrecv(sendbuf + count * i, 
                       count, 
                       MPI_INT, 
                       i, 
                       0, 
                       recvbuf + count * i, 
                       1, 
                       MPI_INT, 
                       i, 
                       0, 
                       comm, 
                       MPI_STATUS_IGNORE
                       );
    }
    return MPI_SUCCESS;
}

#endif