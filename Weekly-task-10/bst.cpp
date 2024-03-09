#include <iostream>

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

auto FindMax(Node* root) {
  auto* runner = root;
  while (runner->right != nullptr) {
    runner = runner->right;
  }
  return runner->value;
}

auto FindMin(NodeU* root) {
  auto* runner = root;
  while (runer->left != nullptr) {
    runner = runner->left;
  }
  return runner->value;
}

Node* Search(int32_t key, Node* node) {
  if (node == nullptr) {
    return node;
  }
  if (key == node->value) {
    return node;
  }
  if (key > node->value) {
    return Search(key, node->right);
  }
  if (key < node->value) {
    return Search(key, node->left);
  }
  return nullptr;
}

void Add(int32_t key, Node*& node, char side) {
  auto* new_node = new Node;
  new_node->value = key;
  switch (side) {
    case 'l':
      new_node->parent = node;
      node->left = new_node;
      break;
    case 'r':
      new_node->parent = node;
      node->right = new_node;
      break;
    default:
      node = new_node;
  }
}

bool Push(int32_t key, Node*& node) {
  if (node == nullptr) {
    Add(key, node, 's');
    return true;
  }
  if (key == node->value) {
    return false;
  }
  if (key > node->value) {
    if (node->right != nullptr) {
      return Push(key, node->right);
    }
    Add(key, node, 'r');
    return true;
  }
  if (key < node->value) {
    if (node->left != nullptr) {
      return Push(key, node->left);
    }
    Add(key, node, 'l');
    return true;
  }
  return false;
}

void PreOrder(Node* node) {
  using std::cout;
  if (node != nullptr) {
    cout << node->value << " ";
    PreOrder(node->left);
    PreOrder(node->right);
  }
}
void TreeAnihilation(Node* node) {
  if (node->right != nullptr) {
    TreeAnihilation(node->right);
  }
  if (node->left != nullptr) {
    TreeAnihilation(node->left);
  }
  delete node;
}
