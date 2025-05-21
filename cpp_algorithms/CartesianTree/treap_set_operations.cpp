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

Node* Erase(Node* T, int x) {
    if (T == nullptr) return nullptr;
    if (T->key == x) T = Merge(T->left, T->right);
    else if (T->key > x) T->left = Erase(T->left, x);
    else T->right = Erase(T->right, x);
    return T;
}

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

int Contains(Node* T, int x, size_t h = 0) {
    if (T == nullptr) return -1;
    if (T->key == x) return h;
    if (T->key > x) return Contains(T->left, x, h+1);
    else return Contains(T->right, x, h+1);
}

int main() {
    size_t n;
    std::cin >> n;
    int x,y;
    std::string command;
    Node* T = nullptr;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> command;
        if (command == "INSERT") {
            std::cin >> x >> y;
            T = Insert(T,new Node(x,y));
        } else if (command == "CONTAINS") {
            std::cin >> x;
            std::cout << Contains(T,x) << std::endl;
        } else if (command == "ERASE") {
            std::cin >> x;
            T = Erase(T,x);
        }
    }
    return 0;
}