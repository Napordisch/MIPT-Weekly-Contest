#include <iostream>

using std::cin;
using std::cout;

template <typename T>
T max(T a, T b) {
  if (a > b) {
    return a;
  }
  return b;
}

struct Node {
  int distance;
  int index;
  Node *left;
  Node *right;
  int height = 1;
};

class Tree {
 public:
  void insert(int key, int distance) { Insert(this->root, key, distance); }

  int GetMin() {
    Node *runner = root;
    while (runner->left != nullptr) {
      runner = runner->left;
    }
    return runner->index;
  }

  int RemoveMin() {
    Node *runner = root;
    if (runner->left == nullptr) {
      Node *prev_root = root;
      root = root->right;
      delete prev_root;
    }
    while(runner->left->left != nullptr) {
      runner = runner->left;
    }
    Node *deleted_node = runner->left;
    if (runner->left->right != nullptr) {
      runner->left = runner->left->right;
      delete deleted_node;
    }
    int index = deleted_node->index;
    return index;
  }

  bool find(int index) {

 private:
  Node *root = nullptr;
  void FixHeight(Node *node) {
    int right_sub_height = 0;
    int left_sub_height = 0;
    if (node->left != nullptr) {
      left_sub_height = node->left->height;
    }
    if (node->right != nullptr) {
      right_sub_height = node->right->height;
    }

    node->height = max(left_sub_height, right_sub_height) + 1;
  }

  void LeftRotation(Node *&node) {
    Node *a = node->right;
    Node *b = node->right->left;
    a->left = node;
    node->right = b;
    node = a;
    FixHeight(node->left);
    FixHeight(node);
  }
  void RightRotation(Node *&node) {
    Node *a = node->left;
    Node *b = node->left->right;
    a->right = node;
    node->left = b;
    node = a;
    FixHeight(node->right);
    FixHeight(node);
  }

  void BigLeftRotation(Node *&node) {
    RightRotation(node->right);
    LeftRotation(node);
  }
  void BigRightRotation(Node *&node) {
    LeftRotation(node->left);
    RightRotation(node);
  }

  int GetBallanceFactor(Node *node) {
    int right_sub_height = 0;
    int left_sub_height = 0;
    if (node->left != nullptr) {
      left_sub_height = node->left->height;
    }
    if (node->right != nullptr) {
      right_sub_height = node->right->height;
    }

    return left_sub_height - right_sub_height;
  }

  void Ballnce(Node *&node) {
    FixHeight(node);
    int bfactor = GetBallanceFactor(node);
    switch (bfactor) {
      case -2:
        if (GetBallanceFactor(node->right) <= 0) {
          LeftRotation(node);
        } else {
          BigLeftRotation(node);
        }
        break;
      case 2:
        if (GetBallanceFactor(node->left) >= 0) {
          RightRotation(node);
        } else {
          BigRightRotation(node);
        }
        break;
    }
  }

  void Insert(Node *&node,
              int distance,
              int index) {
    if (node == nullptr) {
      Node *new_node = new Node;
      new_node->distance = distance;
      new_node->index = index;
      node = new_node;
      return;
    }
    if (distance < node->distance) {
      Insert(node->left, distance, index);
    } else {
      Insert(node->right, distance, index);
    }
    Ballnce(node);
  }
};