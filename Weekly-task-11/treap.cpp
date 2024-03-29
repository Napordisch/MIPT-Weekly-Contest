#include <iostream>

using std::cin;
using std::cout;

struct Node {
  int value;
  int priority = rand();
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

std::pair<Node *, Node *> Split(Node* root, int key) {
  if (root == nullptr) {
    return std::make_pair(nullptr, nullptr);
  }
  if (key < root->value) {
    std::pair<Node*, Node*> split_tree = Split(root->left, key);
    root->left = split_tree.second;
    return std::make_pair(split_tree.first, root);
  }
  std::pair<Node*, Node*> split_tree = Split(root->right, key);
  root->right = split_tree.first;
  return std::make_pair(root, split_tree.second);
}

Node* Merge(Node* left_tree, Node* right_tree) {
  if (left_tree == nullptr) {
    return right_tree;
  }
  if (right_tree == nullptr) {
    return left_tree;
  }
  if (left_tree->priority > right_tree->priority) {
    left_tree->right = Merge(left_tree->right, right_tree);
    return left_tree;
  }
  else {
    right_tree->left = Merge(left_tree, right_tree->left);
    return right_tree;
  }
} 

Node* Insert(Node* tree, int key) {
  Node* elem = new Node;
  elem->value = key;
  std::pair<Node*, Node*> split_tree = Split(tree, key);
  return Merge(Merge(split_tree.first, elem), split_tree.second);
}

Node* Remove(Node* node, int key) {
  if (key > node->value) {
    Remove(node->right, key);
  }
  if (key < node->value) {
    Remove(node->left, key);
  }
  return Merge(node->left, node->right);
}

void TreeAnnihilation(Node *node) {
if (node->right != nullptr) {
    TreeAnnihilation(node->right);
  }
  if (node->left != nullptr) {
    TreeAnnihilation(node->left);
  }
  delete node;
}

bool Find(Node* node, int key) {
  if (node == nullptr) {
    return false;
  }
  if (key > node->value) {
    return Find(node->right, key);
  }
  if (key < node->value) {
    return Find(node->left, key);
  }
  return true;
}

int FindMax(Node* node) {
  if (node == nullptr) {
    return false;
  }
  while (node->right != nullptr) {
    node = node->right;
  }
  return node->value;
}

int FindMin(Node* node) {
  if (node == nullptr) {
    return false;
  }
  while (node->left != nullptr) {
    node = node->left;
  }
  return node->value;
}

int main() {
  Node* tree = nullptr;
  tree = Insert(tree, 2);
  tree = Insert(tree, 123);
  tree = Insert(tree, 5);
  tree = Insert(tree, 23);
  tree = Insert(tree, 43);
  tree = Insert(tree, 13);
  // tree = Remove(tree, 5);
  std::cout << Find(tree, 5) << "\n";
  std::cout << Find(tree, 8)<< "\n";
  std::cout << FindMax(tree)<< "\n";
  std::cout << FindMin(tree) << "\n";
  TreeAnnihilation(tree);
  std::cout << "0";
  return 0;
}