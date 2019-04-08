/*
name: Trevor Greenside
course: CPSC 435 - 01
asgn: Assignment #6
date: 28 February 2019

file: Assignment#6_Greenside.c
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

/*
Creates a matrix of dimension n x n and initializes it with random
values.
*/
int** createMatrix(int n) {
    int** matrix = malloc(n * sizeof(int*));
    int i,j;
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            matrix[i][j] = ((int)rand() % 20000) - 10000;
        }
    }
    return matrix;
}

/*
Creates a matrix with each value initialized to 0.
*/
int** createEmptyMatrix(int n) {
    int** matrix = malloc(n * sizeof(int*));
    int i;
    for (i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
    }
    return matrix;
}

/*
This function prints the values of a matrix type int. To be
used for matrices where n <= 16.
*/
void printMatrix(int** matrix, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        printf("[");
        for (j = 0; j < n; j++) {
            if (j < n-1) {
                printf("%d,", matrix[i][j]);
            }
            else {
                printf("%d", matrix[i][j]);
            }
        }
        printf("]\n");
    }
}

/*
Cleanup function. Clear the matrices from memory.
*/
void freeMatrix(int** matrix, int n) {
    int i;
    for (i = 0; i < n; i++) free(matrix[i]);

    free(matrix);
}

/*
This function serves as a master that sends portions of matrix A and all of B
to each slave, and then it receives their computed output.
*/
void master(int n, int rank, int size) {
    struct timeval tpstart, tpend;
    gettimeofday(&tpstart, NULL);

    int** matrixA = createMatrix(n);
    int** matrixB = createMatrix(n);
    int** matrixC = createEmptyMatrix(n);

    int blockSize = n / (size - 1);
    int extra = (n % (size - 1)) + blockSize;

    // send matrix B to each slave
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 1; j < size; j++) {
            MPI_Send(&matrixB[i][0], n, MPI_INT, j, i, MPI_COMM_WORLD);
        }
    }

    for (i = 1; i < size; i++) {
        // send chunks to each process
        // send start index
        int sendStart = (i - 1) * blockSize;
        MPI_Send(&sendStart, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        // send size
        int sendSize;
        if (i == (size - 1)) sendSize = extra;
        else sendSize = blockSize;

        MPI_Send(&sendSize, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        for (j = 0; j < sendSize; j++)
            MPI_Send(&matrixA[sendStart + j][0], n, MPI_INT, i, 0, MPI_COMM_WORLD);

    }

    for (i = 1; i < size; i++) {
        // receive each portion of matrix C
        int slaveStart = 0;
        int slaveSize = 0;
        MPI_Recv(&slaveStart, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&slaveSize, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (j = slaveStart; j < (slaveStart + slaveSize); j++) {
            MPI_Recv(&matrixC[j][0], n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (n <= 16) {
        printf("Matrix A:\n");
        printMatrix(matrixA, n);
        printf("\nMatrix B:\n");
        printMatrix(matrixB, n);
        printf("\nMatrix C:\n");
        printMatrix(matrixC, n);
    }

    gettimeofday(&tpend, NULL);
    double timeUse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_usec - tpstart.tv_usec);
    printf("Time used where n = %d (us): %f\n", n, timeUse);

    freeMatrix(matrixA, n);
    freeMatrix(matrixB, n);
    freeMatrix(matrixC, n);
}

/*
This function receives rows of matrix A from the Master process, computes
the values for a row in Matrix C, and then sends those rows of matrix C
back to the master.
*/
void slave(int n, int rank, int size) {
    int** matrixB = calloc(n, sizeof(int*));
    int i, j, k;
    for (i = 0; i < n; i++) matrixB[i] = malloc(n * sizeof(int));

    // receive matrixB from each slave
    for (i = 0; i < n; i++) {
        MPI_Recv(&matrixB[i][0], n, MPI_INT, 0, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int start = 0;
    int numRows = 0; // placeholder, to be replaced by recv funciton

    MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&numRows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int** buffer = malloc(numRows * sizeof(int*));
    for (i = 0; i < numRows; i++) {
        buffer[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < numRows; i++) {
        MPI_Recv(&buffer[i][0], n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int** bufferOut = malloc(numRows * sizeof(int*));
    for (i = 0; i < numRows; i++) {
        bufferOut[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                bufferOut[i][j] += (buffer[i][k] * matrixB[k][j]);
            }
        }
    }

    MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&numRows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    for (i = 0; i < numRows; i++) {
        MPI_Send(&bufferOut[i][0], n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    freeMatrix(bufferOut, numRows);
    freeMatrix(buffer, numRows);
    freeMatrix(matrixB, n);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Invalid number of arguments.\nUsage: ./asgn6 <n>\n");
        return 0;
    }

    int n = atoi(argv[1]);
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) return 0;

    if (rank == 0) master(n, rank, size);
    else slave(n, rank, size);

    MPI_Finalize();
    return 0;
}
