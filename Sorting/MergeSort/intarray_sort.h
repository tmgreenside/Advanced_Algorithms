#ifndef INTARRAY_SORT
#define INTARRAY_SORT

/*
The algorithms in this file only sort arrays of integers.

In this file:

1. Bubble sort algorithm
2. Merge sort algorithm
*/

using namespace std;

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

// Copy array portion to entirely new array
void copyArrayNew(int array[], int newArray[], int start, int stop) {
    for (int i = start; i < stop; i++) {
        newArray[i - start] = array[i];
    }
}

// Point to Point copy
void copyArray(int array[], int newArray[], int start, int stop) {
    for (int i = start; i < stop; i++) {
        newArray[i] = array[i];
    }
}

void mergeSortHelper(int array[], int working[], int length) {
    if (length >= 2) {
        int breakPoint = length / 2;
        int left[breakPoint];
        int leftWork[breakPoint];
        int right[length - breakPoint];
        int rightWork[length - breakPoint];
        copyArrayNew(array, left, 0, breakPoint);
        copyArrayNew(array, right, breakPoint, length);
        mergeSortHelper(left, leftWork, breakPoint);
        mergeSortHelper(right, rightWork, (length - breakPoint));

        // merge
        int traceLeft = 0;
        int traceRight = 0;
        int traceWork = 0;
        while (traceLeft < breakPoint && traceRight < (length - breakPoint)) {
            if (leftWork[traceLeft] <= rightWork[traceRight]) {
                working[traceWork] = leftWork[traceLeft++];
            } else {
                working[traceWork] = rightWork[traceRight++];
            }
            traceWork++;
        }
        while (traceLeft < breakPoint) {
            working[traceWork] = leftWork[traceLeft++];
            traceWork++;
        }
        while (traceRight < (length - breakPoint)) {
            working[traceWork] = rightWork[traceRight++];
            traceWork++;
        }
    } else {
        copyArray(array, working, 0, length);
    }
}

/*
Used a TutorialsPoint article as basis for this Merge Sort implementation.

How this works:
Uses recursion to repeatedly break down the array into separate, smaller arrays
until there is only a length of 1, then
*/
void mergeSort(int values[], int length) {
    if (length < 2) return;
    int result[length];
    mergeSortHelper(values, result, length);
    copyArray(result, values, 0, length);
}

#endif
