#include <iostream>
#include <cstdlib>

#include "bst.h"

using namespace std;

int main() {
    BST* myBST = new BST;
    for (int i = 0; i < 6; i++) {
        myBST->addItem(i);
    }
    myBST->printValues();
    cout << myBST->isBalanced() << endl;
    delete myBST;
}
