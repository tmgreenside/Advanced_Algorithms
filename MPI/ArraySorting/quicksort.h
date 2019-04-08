/*
name: Trevor Greenside
course: CPSC 435 - 01
asgn: Assignment #7
date: 7 March 2019

file: quicksort.h
*/

#ifndef QUICKSORT
#define QUICKSORT

/*
This function swaps two numbers.
*/
void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

/*
This function selects the index for where the array will
be broken into two.
*/
int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low;
    int j;
    for (j = low; j < high; j++) {
        if (array[j] < pivot) {
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[high]);
    return i;
}

/*
This function repeatedly -- TODO
*/
void quicksortHelper(int* array, int low, int high) {
    if (low < high) {
        int p = partition(array, low, high);
        quicksortHelper(array, low, p-1);
        quicksortHelper(array, p+1, high);
    }
}

/*
Simple input: takes the array itself and its length as parameters,
and takes advantage of pass by reference to sort the original array.
*/
void quicksort(int* array, int length) {
    quicksortHelper(array, 0, length-1);
}

#endif
