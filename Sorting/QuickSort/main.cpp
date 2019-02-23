#include <iostream>
#include <ctime>

#include "quicksort.h"

using namespace std;
typedef int mytype;

int main(int argc, char** argv) {
    int n;
    if (argc < 2) n = 20; else n = atoi(argv[1]);

    mytype* array = new mytype[n];
    srand((unsigned)time(0));
    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }

    sort(array, 0, n);
    delete[] array;
    return 0;
}
