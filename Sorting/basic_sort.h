#ifndef BASIC_SORT
#define BASIC_SORT

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

#endif
