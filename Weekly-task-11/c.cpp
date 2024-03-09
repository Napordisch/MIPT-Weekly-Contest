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

Node* Insert(Node* tree, int key) {
  auto elem = new Node;
  elem->value = key;
  std::pair<Node*, Node*> split_tree = Split(tree, key);
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
  size_t n;
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    std::string command;
    cin >> command;
    if (command == "push") {
      int elem;
      cin >> elem;
      tree = Insert(tree, elem);
    }
    if (command == "pop") {
      int elem;
      cin >> elem;
      Remove(tree, elem);
    }
    if (command == "get_max") {
      cout << FindMax(tree) << "\n";
    }
    if (command == "get_min") {
      cout << FindMin(tree) << "\n";
    }
    if (command == "find") {
      int elem;
      cin >> elem;
      if (Find(tree, elem)) {
        std::cout << "TRUE"
                  << "\n";
      } else {
        cout << "FALSE"
             << "\n";
      }
    }
  }
  TreeAnnihilation(tree);
  return 0;
}