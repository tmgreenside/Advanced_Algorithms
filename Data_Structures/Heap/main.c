#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "heap.h"

int main(int argc, char** argv) {
    struct heap* myHeap = initHeap();

    int count;
    if (argc > 1) count = atoi(argv[1]);
    else count = 20;

    for (int i = 0; i < count; i++) {
        addToHeap(i, myHeap);
    }

    printHeapValues(myHeap);

    clearHeap(myHeap);
    return 0;
}
