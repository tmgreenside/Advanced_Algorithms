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
    if (length > 2) {
        int midpoint = length / 2;
        int split1[midpoint];
        int work1[midpoint];

        int split2[length - midpoint];
        int work2[length - midpoint];

        copyArrayNew(array, split1, 0, midpoint);
        copyArrayNew(array, split2, midpoint, length);

        mergeSortHelper(split1, work1, midpoint);
        mergeSortHelper(split2, work2, length - midpoint);

        int trace1 = 0, trace2 = 0;
        for (int i = 0; i < length; i++) {
            if (trace1 == (length - midpoint) || work2[trace2] <= work1[trace1]) {
                working[i] = work2[trace2++];
            } else {
                working[i] = work1[trace1++];
            }
        }
    } else if (length == 2) {
        if (array[0] > array[1]) {
            swap(array[0], array[1]);
        }
        copyArrayNew(array, working, 0, 2);
    } else {
        copyArrayNew(array, working, 0, length);
    }
}

/*
Used a TutorialsPoint article as basis for this Merge Sort implementation.
*/
void mergeSort(int values[], int length) {
    if (length < 2) return;
    int working[length];
    mergeSortHelper(values, working, length);
    copyArray(working, values, 0, length);
}

#endif
