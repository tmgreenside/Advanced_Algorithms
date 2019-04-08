/*
name: Trevor Greenside
course: CPSC 435 - 01
asgn: Assignment #7
date: 7 March 2019

file: para.c
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#include "quicksort.h"
#include "basicsort.h"

/*
Build and return a dynamically allocated integer array
populated with random values.
*/
int* generateArray(int n) {
    int* array = malloc(n*sizeof(int));
    srand((unsigned)time(0));
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 2000 - 1000;
    }
    return array;
}

/*
This function compares and splits a local and a remote list. Note that this
function assumes that both the local list and the remote list are already
sorted.
*/
void CompareSplit(int nlocal, int* arrayLocal, int* arrayReceive, int* arrayWorking, int keepsmall) {
    int i, j, k;

    for (i = 0; i < nlocal; i++) {
        arrayWorking[i] = arrayLocal[i];
    }

    if (keepsmall) {
        for (i=j=k=0; k < nlocal; k++) {
            if (j == nlocal || (i < nlocal && arrayWorking[i] < arrayReceive[j])) {
                arrayLocal[k] = arrayWorking[i++];
            }
            else {
                arrayLocal[k] = arrayReceive[j++];
            }
        }
    }
    else {
        for (i=k=nlocal-1, j=nlocal-1; k >= 0; k--) {
            if (j == -1 || (i >= 0 && arrayWorking[i] >= arrayReceive[j]))
                arrayLocal[k] = arrayWorking[i--];
            else
                arrayLocal[k] = arrayReceive[j--];
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: asgn7para <array size>\n");
        return 0;
    }
    int n = atoi(argv[1]);

    int rank, size;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    int nlocal = n / size;
    int* arrayLocal = malloc(nlocal*sizeof(int));
    int* array;
    if (rank == 0) {
        array = generateArray(n);
    }

    struct timeval tpstart, tpend;
    if (rank == 0)
        gettimeofday(&tpstart, NULL);

    MPI_Scatter(array, nlocal, MPI_INT, arrayLocal, nlocal, MPI_INT, 0, MPI_COMM_WORLD);
    bubbleSort(arrayLocal, nlocal);

    int oddrank, evenrank;

    if (rank%2 == 0) {
        oddrank = rank - 1;
        evenrank = rank + 1;
    }
    else {
        oddrank = rank + 1;
        evenrank = rank - 1;
    }

    if(oddrank == -1 || oddrank == size)
        oddrank = MPI_PROC_NULL;
    if(evenrank == -1 || evenrank == size)
        evenrank = MPI_PROC_NULL;

    int* arrayReceive = malloc(nlocal * sizeof(int));
    int* arrayWorking = malloc(nlocal * sizeof(int));

    for (i = 0; i < size; i++) {
        if (i%2 == 1) {
            MPI_Sendrecv(arrayLocal, nlocal, MPI_INT, oddrank, 1, arrayReceive, nlocal, MPI_INT, oddrank, 1, MPI_COMM_WORLD, &status);
            if (rank != 0 && rank != (size-1)) {
                CompareSplit(nlocal, arrayLocal, arrayReceive, arrayWorking, rank<status.MPI_SOURCE);
            }
        }
        else {
            MPI_Sendrecv(arrayLocal, nlocal, MPI_INT, evenrank, 1, arrayReceive, nlocal, MPI_INT, evenrank, 1, MPI_COMM_WORLD, &status);
            CompareSplit(nlocal, arrayLocal, arrayReceive, arrayWorking, rank<status.MPI_SOURCE);
        }
    }

    int* arrayIn;
    if (rank == 0)
        arrayIn = malloc(n*sizeof(int));

    MPI_Gather(arrayLocal, nlocal, MPI_INT, arrayIn, nlocal, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0 && n <= 40)
        displayArray(arrayIn, n);

    if (rank == 0) {
        printf("Gather complete.\n");
        gettimeofday(&tpend, NULL);
        double timeUse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_usec - tpstart.tv_usec);
        printf("Time used where n = %d (us): %f\n", n, timeUse);
        free(array);
    }

    free(arrayLocal);
    free(arrayReceive);
    free(arrayWorking);
    MPI_Finalize();

    return 0;
}
