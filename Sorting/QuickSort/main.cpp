#include <iostream>
#include <ctime>

#include "quicksort.h"

using namespace std;
typedef int mytype;

void displayArray(int* array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d\n", array[i]);
    }
}

int main(int argc, char** argv) {
    int n;
    if (argc < 2) n = 20; else n = atoi(argv[1]);

    mytype* array = new mytype[n];
    srand((unsigned)time(0));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 10000;
    }

    cout << "Before:" << endl;
    displayArray(array, n);
    quicksort(array, n);
    cout << endl << "After:" << endl;
    displayArray(array, n);

    delete[] array;
    return 0;
}
