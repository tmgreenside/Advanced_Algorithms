#ifndef INTARRAY_SORT
#define INTARRAY_SORT

/*
The algorithms in this file only sort arrays of integers.

In this file:

1. Bubble sort algorithm
2. Merge sort algorithm
*/

using namespace std;

void mergeSortHelper(int array[], )
void copyArray(int array[], int newArray[], int start, int stop);

void bubbleSort(int values[], int length) {
    if (length < 2) return;

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < length - 1; i++) {
            if (values[i] > values[i+1]) {
                swap(values[i], values[i+1]);
                sorted = false;
            }
        }
    }
}

/*
Used a TutorialsPoint article as basis for this Merge Sort implementation.
*/
void mergeSort(int values[], int length) {
    if (length < 2) return;

    int workArray[length];
    copyArray(values, workArray, 0, length);

    mergeSortHelperSplit(workArray, 0, length, values);
}

void copyArray(int array[], int newArray[], int start, int stop) {
    for (int i = start; i < stop; i++) {
        newArray[i] = array[i];
    }
}

#endif
