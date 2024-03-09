#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

struct Node {
  int x;
  int y = rand();
  Node *left = nullptr;
  Node *right = nullptr;
};

class Treap {
 private:
  Node *root_ = nullptr;
  unsigned int planned_requests_;

  std::pair<Node *, Node *> Split(Node *tree, int key) {
    if (tree == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }
    if (key > tree->x) {
      std::pair<Node *, Node *> split_tree = Split(tree->right, key);
      tree->right = split_tree.first;
      return std::make_pair(tree, split_tree.second);
    }
    std::pair<Node *, Node *> split_tree = Split(tree->left, key);
    tree->left = split_tree.second;
    return std::make_pair(split_tree.first, tree);
  }

  Node *Merge(Node *l, Node *r) {
    if (l == nullptr) {
      return r;
    }
    if (r == nullptr) {
      return l;
    }

    if (l->y > r->y) {
      l->right = Merge(l->right, r);
      return l;
    }
    r->left = Merge(l, r->left);
    return r;
  }

  auto FindMax(Node *root) {
    auto *runner = root;
    while (runner->right != nullptr) {
      runner = runner->right;
    }
    return runner->x;
  }

  Node *PrInsert(Node *tree, int key) {
    auto split_tree = Split(tree, key);
    Node *l = split_tree.first;
    Node *r = split_tree.second;
    auto *new_node = new Node;
    new_node->x = key;
    l = Merge(l, new_node);
    tree = Merge(l, r);
    return tree;
  }

  void PrInOrder(Node *node) {
    using std::cout;
    if (node != nullptr) {
      PrInOrder(node->left);
      cout << node->x << "\n";
      PrInOrder(node->right);
    }
  }

  // Node* remove (Node* tree, int key) {
  //   std::pair<Node*, Node*> split_tree = Split(tree, key);
  //   Node* l = split_tree.first;
  //   Node* r = split_tree.second;
  //   RemoveMax();
  //   tree = Merge(l, r);
  //   return tree;
  // }
  auto FindMin(Node *root) {
    auto *runner = root;
    while (runner->left != nullptr) {
      runner = runner->left;
    }
    return runner->x;
  }

  Node *Search(int32_t key, Node *node) {
    if (node == nullptr) {
      return node;
    }
    if (key == node->x) {
      return node;
    }
    if (key > node->x) {
      return Search(key, node->right);
    }
    if (key < node->x) {
      return Search(key, node->left);
    }
    return nullptr;
  }

  void RemoveMax(Node *&node) {
    while (node->right != nullptr) {
      RemoveMax(node->right);
    }
    if (node->right == nullptr) {
      node = node->left;
    }
  }
  Node *Remove(Node *tree, int key) {
    auto split_tree = Split(tree, key);
    auto l = split_tree.first;
    auto r = split_tree.second;
    RemoveMax(l);
    tree = Merge(l, r);
    return tree;
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

 public:
  void Push(int key) {
    this->root_ = PrInsert(this->root_, key);
  }

  void InOrder() {
    PrInOrder(this->root_);
  }

  auto PGetMin() {
    return FindMin(this->root_);
  }

  auto PGetMax() {
    return FindMax(this->root_);
  }

  void PSetPlannedRequests(unsigned int n) {
    this->planned_requests_ = n;
  }

  bool Find(int key) {
    return !(Search(key, this->root_) == nullptr);
  }

  void Pop(int key) {
    Remove(this->root_, key);
  }
  void Annihilate() {
    TreeAnnihilation(this->root_);
  }
};

int main() {
  Treap treap;
  while (true) {
    int n;
    std::cin >> n;
    if (n == 0) {
      break;
    }
    treap.Push(n);
  }
  treap.InOrder();
  treap.Annihilate();
  return 0;
}