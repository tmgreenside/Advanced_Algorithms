#ifndef HEAP
#define HEAP

// reference here: https://www.tutorialspoint.com/data_structures_algorithms/heap_data_structure.htm

struct node {
    int value;
    struct node* left;
    struct node* right;
};

struct heap {
    int height;
    struct node* head;
};

struct heap* initHeap();
void clearHeap(struct heap* theHeap);
void addToHeap(int value, struct heap* theHeap);
void printHeapValues(struct heap* theHeap);


struct heap* initHeap() {
    struct heap* theHeap = malloc(sizeof(struct heap));
    theHeap->height = 0;
    theHeap->head = NULL;
    return theHeap;
}

void clearHeapHelper(struct node* head) {
    if (head->left) clearHeapHelper(head->left);
    if (head->right) clearHeapHelper(head->right);
    free(head);
}

void clearHeap(struct heap* theHeap) {
    if (theHeap->height > 0)
        clearHeapHelper(theHeap->head);
    free(theHeap);
}

int addToHeapLevel(int value, struct node* head, int level) {
    if (level > 1) {
        if (head->left){
            if (!head->right){
                head->right = malloc(sizeof(struct node));
                head->right->value = value;
                head->right->left = NULL;
                head->right->right = NULL;
                return 1;
            } else return 0;
        } else {
            head->left = malloc(sizeof(struct node));
            head->left->value = value;
            head->left->left = NULL;
            head->left->right = NULL;
            return 1;
        }
    } else return 0;
}

void newHeapLevel(int value, struct node* head) {
    if (head->left) newHeapLevel(value, head->left);
    else {
        head->left = malloc(sizeof(struct node));
        head->left->value = value;
        head->left->right = NULL;
        head->left->left = NULL;
    }
}

void addToHeap(int value, struct heap* theHeap) {
    if (theHeap->height == 0) {
        theHeap->head = malloc(sizeof(struct node));
        theHeap->head->value = value;
        theHeap->head->left = NULL;
        theHeap->head->right = NULL;
    } else {
        // replace value and head value if new value is greater
        if (value > theHeap->head->value) {
            int sub = value;
            value = theHeap->head->value;
            theHeap->head->value = sub;
        }

        // try to add to the lowest level
        if (addToHeapLevel(value, theHeap->head, theHeap->height)) return;

        // TODO: if fail, add new layer
        newHeapLevel(value, theHeap->head);
    }
    theHeap->height++;
}

void printHeapHelper(struct node* head) {
    if (head->left) printHeapHelper(head->left);
    printf("%d ", head->value);
    if (head->right) printHeapHelper(head->right);
}

void printHeapValues(struct heap* theHeap) {
    printHeapHelper(theHeap->head);
    printf("\n");
}

#endif
