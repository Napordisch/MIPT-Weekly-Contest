#include <iostream>

struct Node {
  int32_t value;
  Node* next = nullptr;
  Node* prev = nullptr;
};

void PushFront(int32_t new_value, Node*& root) {
  auto* new_node = new Node;
  new_node->value = new_value;
  new_node->next = root;
  if (root != nullptr) {
    root->prev = new_node;
  }
  new_node->prev = nullptr;
  root = new_node;
}

void PopFront(Node*& root) {
  if (root == nullptr) {
    return;
  }
  // std::cout << root->value << "\n";
  Node* new_node = root->next;
  delete root;
  root = new_node;
  root->prev = nullptr;
}

int32_t Size(Node* root) {
  int32_t count = 0;
  Node* runner = root;
  while (runner != nullptr) {
    count++;
    runner = runner->next;
  }
  std::cout << count << "\n";
  return count;
}

void PushBack(int32_t new_value, Node*& root) {
  if (root == nullptr) {
    PushFront(new_value, root);
    return;
  }

  Node* runner = root;
  while (runner->next != nullptr) {
    runner = runner->next;
  }

  auto* new_node = new Node;
  new_node->value = new_value;
  new_node->next = nullptr;
  new_node->prev = runner;
  runner->next = new_node;
}

void PopBack(Node*& root) {
  if (root == nullptr) {
    return;
  }
  if (root->next == nullptr) {
    PopFront(root);
  }
  Node* runner = root;
  while (runner->next->next != nullptr) {
    runner = runner->next;
  }
  delete runner->next;
  runner->next = nullptr;
}

void Add(int32_t new_value, Node*& previous) {
  auto* new_node = new Node;
  new_node->value = new_value;
  new_node->next = previous->next;
  new_node->next->previous = new_node;
  previous->next = new_node;
  new_node->prev = previous;
}

void Remove(Node*& current) {
  current->prev->next = current->next;
  delete current;
}

void Delete(Node*& root) {
  Node* runner = root;
  while (runner != nullptr) {
    Node* next = runner->next;
    delete runner;
    runner = next;
  }
  root = nullptr;
}
void Print(Node* root) {
  // std::cout << "test";
  Node* runner = root;
  while (runner) {
    std::cout << runner->value << " -> ";
    runner = runner->next;
  }
  std::cout << "X"
            << "\n";
}

void PrintLastPrev(Node* root) {
  // std::cout << "test";
  Node* runner = root;
  while (runner->next != nullptr) {
    runner = runner->next;
  }
  if (runner != nullptr && runner->prev != nullptr) {
    std::cout << runner->prev->value << "\n";
  }
}

void Back(Node* root) {
  Node* runner = root;
  while (runner->next != nullptr) {
    runner = runner->next;
  }
  std::cout << runner->value << "\n";
}

int32_t main() {
  Node* root = nullptr;
  while (true) {
    std::string command;
    std::cin >> command;
    if (command == "push") {
      int32_t elem;
      std::cin >> elem;
      PushFront(elem, root);
      std::cout << "ok"
                << "\n";
    }
    if (command == "pop") {
      PopFront(root);
    }
    if (command == "back") {
      std::cout << root->value << "\n";
    }
    if (command == "clear") {
      Delete(root);
      std::cout << "ok"
                << "\n";
    }
    if (command == "exit") {
      std::cout << "bye"
                << "\n";
      break;
    }
    if (command == "display") {
      Print(root);
    }
    if (command == "size") {
      Size(root);
    }
    if (command == "lastprev") {
      std::cout << "test" << "\n";
      PrintLastPrev(root);

    }
  }
  Delete(root);
  delete root;
  return 0;
}