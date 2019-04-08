/*
name: Trevor Greenside
course: CPSC 435 - 01
asgn: Assignment #7
date: 7 March 2019

file: basicsort.h
*/

#ifndef BASICSORT
#define BASICSORT

/*
This function prints out the values in an integer array.
*/
void displayArray(int* array, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%d\n", array[i]);
    }
}

/*
Implementation of a simple bubble sort algorithm.
*/
void bubbleSort(int* values, int length) {
    if (length < 2) return;

    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        int i;
        for (i = 0; i < length - 1; i++) {
            if (values[i] > values[i+1]) {
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;

                sorted = 0;
            }
        }
    }
}

#endif
