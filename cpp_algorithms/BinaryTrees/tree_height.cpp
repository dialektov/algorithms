#include <iostream>

struct Node {
  int value;
  Node *left_son;
  Node *right_son;
  Node(int value) : value(value), left_son(nullptr), right_son(nullptr) {}
};

Node* push_node(Node* root, int value) {
  if (root == nullptr) {
    return new Node(value);
  }
  if (value < root->value) {
    root->left_son = push_node(root->left_son, value);
  } else if (value > root->value) {
    root->right_son = push_node(root->right_son, value);
  }
  return root;
}

int get_height(Node *root) {
  if (root == nullptr) {
    return 0;
  }
  return std::max(get_height(root->left_son), get_height(root->right_son)) + 1;
}

int main() {
  Node *root = nullptr;
  int value;
  while (std::cin >> value && value != 0) root = push_node(root, value);
  std::cout << get_height(root) << std::endl;
  return 0;
}