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

std::pair<Node*, Node*> Split(Node* root, int key) {
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
  right_tree->left = Merge(left_tree, right_tree->left);
  return right_tree;
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

Node* Insert(Node* tree, int key) {
  std::pair<Node*, Node*> split_tree = Split(tree, key);
  if (FindMax(split_tree.first) == key) {
    return Merge(split_tree.first, split_tree.second);
  }
  auto elem = new Node;
  elem->value = key;
  return Merge(Merge(split_tree.first, elem), split_tree.second);
}

void Remove(Node* node, int key) {
  if (node == nullptr) {
    return;
  }
  if (key > node->value) {
    if (node->right != nullptr) {
      if (node->right->value == key) {
        Node* temp_right_node = node->right;
        node->right = Merge(temp_right_node->left, temp_right_node->right);
        delete temp_right_node;
        return;
      }
      Remove(node->right, key);
    }
  }
  if (key < node->value) {
    if (node->left != nullptr) {
      if (node->left->value == key) {
        Node* temp_left_node = node->left;
        node->left = Merge(temp_left_node->left, temp_left_node->right);
        delete temp_left_node;
        return;
      }
      Remove(node->left, key);
    }
  }
}

void TreeAnnihilation(Node* node) {
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

int FindMin(Node* node) {
  if (node == nullptr) {
    return false;
  }
  while (node->left != nullptr) {
    node = node->left;
  }
  return node->value;
}

void InOrder(Node* node) {
  using std::cout;
  if (node != nullptr) {
    InOrder(node->left);
    cout << node->value << "\n";
    InOrder(node->right);
  }
}

int main() {
  using std::cin;
  using std::cout;
  Node* root = nullptr;
  while (true) {
    int input;
    cin >> input;
    if (input == 0) {
      break;
    }
    root = Insert(root, input);
  }
  InOrder(root);
  TreeAnnihilation(root);
  return 0;
}