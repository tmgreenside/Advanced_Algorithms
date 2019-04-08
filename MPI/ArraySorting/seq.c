/*
name: Trevor Greenside
course: CPSC 435 - 01
asgn: Assignment #7
date: 7 March 2019

file: seq.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#include "quicksort.h"
#include "basicsort.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: asgn7seq <array size>\n");
        return 0;
    }

    int n = atoi(argv[1]);
    int* array = malloc(n*sizeof(int));
    srand((unsigned)time(0));
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 2000 - 1000;
    }

    struct timeval tpstart, tpend;
    gettimeofday(&tpstart, NULL);

    quicksort(array, n);

    gettimeofday(&tpend, NULL);
    double timeUse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_usec - tpstart.tv_usec);
    printf("Time used where n = %d (us): %f\n", n, timeUse);
    free(array);
    return 0;
}
