#include <iostream>

using namespace std;

bool verifySorted(int* array, int length) {
    for (int i = 0; i < length; i++) {
        if (array[i+1] && array[i] > array[i+1])
            return false;
    }
    return  true;
}

int main(int argc, char** argv) {

}
