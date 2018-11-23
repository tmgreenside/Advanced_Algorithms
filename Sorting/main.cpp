#include <iostream>
#include <cstdlib>
#include <ctime>

#include "intarray_sort.h"

using namespace std;

int main(int argc, char** argv) {
    int array_size, max_value;
    if (argc > 2) max_value = atoi(argv[2]); else max_value = 20000;
    if (argc > 1) array_size = atoi(argv[1]); else array_size = 100;

    cout << "Got here" << endl;

    srand(time(0));

    int values[array_size];
    for (int i = 0; i < array_size; i++) {
        values[i] = rand() % (max_value * 2) - max_value;
        cout << values[i] << endl;
    }

    bubbleSort(values, array_size);

    cout << endl << "Sorted" << endl;

    for (int i = 0; i < array_size; i++) {
        cout << values[i] << endl;
    }

    return 0;
}
