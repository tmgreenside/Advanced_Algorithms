#ifndef QUICKSORT
#define QUICKSORT

typedef int mytype;
using namespace std;

int partition(int* array, int low, int high) {
    int pivot = array[high-1];
    int i = low;
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            swap(array[i], array[j]);
            i++;
        }
    }
    swap(array[i], array[high]);
    return i;
}

void quicksort(int* array, int low, int high) {
    if (low < high) {
        int p = partition(array, low, high);
        quicksort(array, low, p);
        quicksort(array, p, high);
    }
}

#endif
