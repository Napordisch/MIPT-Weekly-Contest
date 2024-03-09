#include <cstdlib>
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

auto FindMin(Node* root) {
  auto* runner = root;
  while (runner->left != nullptr) {
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

//

void InOrder(Node* node) {
  using std::cout;
  if (node != nullptr) {
    InOrder(node->left);
    cout << node->value << " ";
    InOrder(node->right);
  }
}

int32_t Height(Node* root, bool& tree_balanced) {
  int32_t left_height = 0;
  if (root->left != nullptr) {
    left_height = Height(root->left, tree_balanced);
  }
  int32_t right_height = 0;
  if (root->right != nullptr) {
    right_height = Height(root->right, tree_balanced);
  }
  if (left_height - right_height > 1 or right_height - left_height > 1) {
    tree_balanced = false;
  }
  uint32_t height = (left_height > right_height ? left_height : right_height) + 1;
  return height;
}

int main() {
  using std::cin;
  using std::cout;
  Node* root = nullptr;
  int32_t amount = 0;
  while (true) {
    int32_t input;
    cin >> input;
    if (input == 0) {
      break;
    }
    if (Push(input, root)) {
      amount++;
    }
  }

  bool tree_balanced = true;
  if (root != nullptr) {
    Height(root, tree_balanced);
  }

  if (tree_balanced) {
    cout << "YES";
  } else {
    cout << "NO";
  }
  if (root != nullptr) {
    TreeAnihilation(root);
  }
  return 0;
}