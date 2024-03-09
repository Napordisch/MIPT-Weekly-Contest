#include <iostream>

struct Node {
  int key;
  int height;
  Node* left;
  Node* right;
  Node* parent;
};

struct QNode {
  Node* value;
  QNode* next;
  QNode* previous;
};

void Push(QNode*& root, Node* value) {
  QNode* new_node = new QNode;
  new_node->value = value;
  if (root == nullptr) {
    root = new_node;
    return;
  }
  QNode* runner = root;
  while (runner->next != nullptr) {
    runner = runner->next;
  }
  runner->next = new_node;
}

Node* Pop(QNode*& root) {
  if(root != nullptr) {
    Node* popping_value = root->value;
    QNode* next = root->next;
    delete root;
    root = next;
    return popping_value;
  }
  return nullptr;
}

template <typename T>
auto max(T a, T b) {
  if (a > b) {
    return a;
  }
  return b;
}

int height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

void FixHeight(Node* node) {
  int left_height = height(node->left);
  int right_height = height(node->right);
  node->height = max(left_height, right_height) + 1;
}

auto bfactor(Node* node) {
  return height(node->left) - height(node->right);
}

Node* LeftRotation(Node* node) {
  Node* c = node->right->left;
  Node* b = node->right;
  b->left = node;
  node->right = c;
  FixHeight(b->left);
  FixHeight(b);
  return b;
}

// Node* RightRotation(Node* node){ 
//   Node* c = node->left->right;
//   Node* b = node->left;
//   b->right = node;
//   node->left = c;
//   FixHeight(b->right);
//   FixHeight(b);
//   return b
// }

Node *RightRotation(Node *node) {
 Node *a = node->left;
 Node *c = a->right;

 node->left = c;
 a->right = node;

 FixHeight(node);
 FixHeight(a);

 return a;
}

// Node* BigLeftRotation(Node* node) {
//   node->right = RightRotation(node->right);
//   return LeftRotation(node);
// }

// Node* BigRightRotation(Node* node) {
//   node->left = LeftRotation(node->left);
//   return RightRotation(node);
// }

Node* BigLeftRotation(Node* a) {
  Node* b = a->right;
  Node* c = b->left;
  Node* m = c->left;
  Node* n = c->right;
  a->right = m;
  b->right = n;
  c->left = a;
  c->right = b;
  FixHeight(a);
  FixHeight(b);
  FixHeight(c);
  return c;
}

// Node* BigRightRotation(Node* a) {
//   Node* b = a->left;
//   Node* c = b->right;
//   Node* m = c->right;
//   Node* n = c->left;
//   a->left = m;
//   b->left = n;
//   c->right = a;
//   c->left = b;
//   FixHeight(a);
//   FixHeight(b);
//   FixHeight(c);
//   return c;
// }

Node* ballance(Node* node) {
  FixHeight(node);
  int b_factor = bfactor(node);
  if (b_factor == 2) {
    if (bfactor(node->right) >= 0) {
      return LeftRotation(node);
    }
    return BigLeftRotation(node);
  }
  if (b_factor == -2) {
    if (bfactor(node->left) <= 0) {
      return RightRotation(node);
    }
    return BigRightRotation(node);
  }
  return node;
}

Node* insert(Node* tree, int key) {
  if (tree == nullptr) {
    auto* node = new Node;
    node->key = key;
    node->height = 1;
    return node;
  }
  if (key < tree->key) {
    tree->left = insert(tree->left, key);
  } else {
    tree->right = insert(tree->right, key);
  }
  return ballance(tree);
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

void BFS(Node* node) {
  QNode* queue = nullptr;
  Push(queue, node);
  while (queue != nullptr) {
    node = Pop(queue);
    std::cout << node->key << "\n";
    if (node->left != nullptr) {
      Push(queue, node->left);
    }
    if (node->right != nullptr) {
      Push(queue, node->right);
    }
  }
}

void InOrder(Node* node) {
  using std::cout;
  if (node != nullptr) {
    InOrder(node->left);
    cout << node->key << "\n";
    InOrder(node->right);
  }
}

int main() {
  Node* root = nullptr;
  // while (true) {
  //   int value;
  //   std::cin >> value;
  //   if (value == 0) {
  //     break;
  //   }
  //   root = insert(root, value);
  // }
  root = insert(root, 7);
  root = insert(root, 3);
  root = insert(root, 2);
  root = insert(root, 1);
  root = insert(root, 9);
  root = insert(root, 5);
  root = insert(root, 4);
  root = insert(root, 6);
  root = insert(root, 8);

  InOrder(root);
  // BFS(root);
  TreeAnnihilation(root);
  return 0;
}