#include <iostream>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int Height(Node* node) {
    return node ? node->height : 0;
}

int Balance(Node* node) {
    return node ? Height(node->left) - Height(node->right) : 0;
}

void upHeight(Node* node) {
    node->height = 1 + max(Height(node->left), Height(node->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    upHeight(y);
    upHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    upHeight(x);
    upHeight(y);
    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    upHeight(node);
    int balance = Balance(node);
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int n, key;
    cout << "Number: ";
    cin >> n;
    cout << " Keys : ";
    for (int i = 0; i < n; ++i) {
        cin >> key;
        root = insert(root, key);
    }
    cout << "In-order tree: ";
    inOrder(root);
    cout << endl;
}
