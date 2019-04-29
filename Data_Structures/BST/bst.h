#ifndef BST_H
#define BST_H

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

class BST {
public:
    BST() {
        head = nullptr;
    }

    ~BST() {
        cleanupHelper(head);
    }

    Node* createNode (int value) {
        Node* node = new Node;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    void addItem(int value) {
        if (head == nullptr) {
            cout << "IS null" << endl;
            head = createNode(value);
        }
        else {
            Node* node = head;
            while (true) {
                if (value <= node->value) {
                    if (node->left == nullptr) {
                        node->left = createNode(value);
                        break;
                    }
                    else
                        node = node->left;
                } else {
                    cout << node->value << endl;
                    if (node->right == nullptr) {
                        node->right = createNode(value);
                        break;
                    }
                    else
                        node = node->right;
                }
            }
        }
        cout << value << " inserted" << endl;
    }

    bool isBalanced() {
        if (isBalancedHelper(head)) {
            cout << "Is balanced" << endl;
            return true;
        }
        else {
            cout << "Not balanced" << endl;
            return false;
        }
    }

    bool isBalancedHelper(Node* node) {
        if (node == nullptr) {
            return true;
        }
        else {
            int heightLeft = getHeight(node->left);
            int heightRight = getHeight(node->right);
            if (abs(heightLeft - heightRight) <= 1) {
                if (isBalancedHelper(node->left) && isBalancedHelper(node->right)) {
                    return true;
                }
            }
            return false;
        }
    }

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            return 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    int max(int val1, int val2) {
        if (val1 < val2) return val2;
        return val1;
    }

    void printValues() {
        printHelper(head);
    }

    void printHelper(Node* node) {
        if (node != nullptr) {
            printHelper(node->left);
            cout << node->value << endl;
            printHelper(node->right);
        }
    }

    void cleanupHelper(Node* node) {
        if (node != nullptr) {
            if (node->left != nullptr) cleanupHelper(node->left);
            if (node->right != nullptr) cleanupHelper(node->right);
            delete node;
        }
    }

private:
    Node* head;
};

#endif
