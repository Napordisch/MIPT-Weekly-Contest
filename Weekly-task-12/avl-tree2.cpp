#include <iostream>

using std::cin;
using std::cout;

struct Node {
  int key;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  int height;
};

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int BFactor(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return Height(node->left) - Height(node->right);
}

void FixHeight(Node* node) {
  int left_height = Height(node->left);
  int right_height = Height(node->right);
  node->height = max(left_height, right_height) + 1;
}

Node *LeftRotation(Node *node) {
  Node *y = node->right;
  Node *u = y->left;
  y->left = node;
  y->left->right = u;
  node = y;
  FixHeight(node->left);
  FixHeight(node);
  return node;
}

Node *RightRotation(Node *node) {
  Node *y = node->left;
  Node *u = y->right;
  y->right = node;
  y->right->left = u;
  node = y;
  FixHeight(node->right);
  FixHeight(node);
  return node;
}

Node *BigLeftRotation(Node *node) {
  node->right = RightRotation(node->right);
  node = LeftRotation(node);
  return node;
}

Node *BigRightRotation(Node *node) {
  node->left = LeftRotation(node->left);
  node = RightRotation(node);
  return node;
}

Node *Ballance(Node *node) {
  FixHeight(node);
  int b_factor = BFactor(node);
  if (b_factor == -2) {
    if (BFactor(node->right) <= 0) {
      return LeftRotation(node);
    } else {
      return BigLeftRotation(node);
    }
  }
  if (b_factor == 2) {
    if (BFactor(node->left) <= 0) {
      return RightRotation(node);
    } else {
      return BigRightRotation(node);
    }
  }
  return node;
}

Node *Insert(Node *node, int key) {
  if (node == nullptr) {
    Node *new_node = new Node;
    new_node->key = key;
    return new_node;
  }
  if (key > node->key) {
    node->right = Insert(node->right, key);
  } else {
    node->left = Insert(node->left, key);
  } 
  return Ballance(node);
}

int main() {
  Node* root = nullptr;
  root = Insert(root, 10);
  root = Insert(root, 23);
  root = Insert(root, 1);
  root = Insert(root, 24);
  root = Insert(root, 123);
  root = Insert(root, 34);
  return 0;
}