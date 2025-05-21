#include <iostream>
#include <vector>

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
    Node(int key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}
};

std::pair<Node*,Node*> Split(Node* T, int x) {
    if (T == nullptr) return {nullptr, nullptr};
    if (x > T->key) {
        std::pair<Node*,Node*> para = Split(T->right, x);
        T->right = para.first;
        return {T,para.second};
    } else {
        std::pair<Node*,Node*> para = Split(T->left, x);
        T->left = para.second;
        return {para.first,T};
    }
}

Node* Merge(Node* T1, Node* T2) {
    if (T1 == nullptr) return T2;
    if (T2 == nullptr) return T1;
    if (T1->priority > T2->priority) {
        T1->right = Merge(T1->right, T2);
        return T1;
    } else {
        T2->left = Merge(T1, T2->left);
        return T2;
    }
}

Node* Insert(Node* T, Node* k) {
    auto para = Split(T,k->key);
    T = Merge(Merge(para.first,k),para.second);
    return T;
}

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

int main() {
    size_t n;
    std::cin >> n;
    int x,y;
    std::cin >> x >> y;
    Node* T = new Node(x,y);
    for (size_t i = 1; i < n; ++i) {
        std::cin >> x >> y;
        T = Insert(T,new Node(x,y));
    }
    std::cout << getHeight(T)-1;
    return 0;
}