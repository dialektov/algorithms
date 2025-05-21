#include <iostream>
#include <set>
#include <stack>

struct Node {
    int value;
    Node *left_son;
    Node *right_son;
    Node(int value) : value(value), left_son(nullptr), right_son(nullptr) {}
};

void push_node(Node *&root, int value) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }
    if (value < root->value) {
        push_node(root->left_son, value);
    } else if (value > root->value) {
        push_node(root->right_son, value);
    }
}

void find_branches(Node* root, std::set<int>& ans) {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        if ((current->left_son != nullptr && current->right_son == nullptr) || (current->left_son == nullptr && current->right_son != nullptr)) {
            ans.insert(current->value);
        }
        if (current->right_son != nullptr) {
            st.push(current->right_son);
        }
        if (current->left_son != nullptr) {
            st.push(current->left_son);
        }
    }
}

int main() {
    Node *root = nullptr;
    int value;
    while (std::cin >> value && value != 0) {
        push_node(root, value);
    }
    std::set<int> ans;
    find_branches(root, ans);
    for (auto i : ans) {
        std::cout << i << std::endl;
    }
    return 0;
}