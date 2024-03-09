#include <iostream>

struct Node {
  int value;
  Node* next = nullptr;
};

void PushFront(int new_value, Node*& root){
  Node* new_node = new Node;
  new_node->value = new_value;
  new_node->next = root;
  root = new_node;
}

void PopFront(Node*& root){
  if (root == nullptr){
    return;
  }
  Node* new_node = root->next;
  delete root;
  root = new_node;
}

int32_t Size(Node* root){
  int32_t count = 0;
  Node* runner = root;
  while (runner != nullptr){
    count++;
    runner = runner-> next;
  }
  return count;
}

void PushBack(int new_value, Node*& root){
  if (root == nullptr){
    PushFront(new_value, root);
    return;
  }

  Node* runner = root;
  while (runner->next != nullptr) {
    runner = runner->next;
  }

  Node* new_node = new Node;
  new_node->value = new_value;
  new_node->next = nullptr;
  runner->next = new_node;
}

void PopBack(Node*& root){
  if (root == nullptr){
    return;
  }
  if (root->next == nullptr){
    PopFront(root);
  }
  Node* runner = root;
  while (runner->next->next != nullptr){
    runner = runner->next;
  }
  delete runner->next;
  runner->next = nullptr;
}

void Add(int new_value, Node*& previous){
  Node* new_node = new Node;
  new_node->value = new_value;
  new_node->next = previous->next;
  previous->next = new_node;
}

void Remove(Node*& previous){
  Node* current = previous->next;
  previous->next = current->next;
  delete current;
}

void Delete(Node*& root){
  Node* runner = root;
  while (runner != nullptr){
    Node* next = runner->next;
    delete runner;
    runner = next;
  }
  root = nullptr;
}
void Print(Node* root){
  // std::cout << "test";
  Node* runner = root;
  while (runner){
    std::cout << runner->value << " -> ";
    runner = runner->next;
  }
  std::cout << "X" << "\n";
}

int main() {
  // std::cout << "test";
  Node* root_node_ptr = new Node;
  root_node_ptr->value = 10;
  PushBack(7, root_node_ptr);
  PushFront(3, root_node_ptr);
  PushBack(13, root_node_ptr);
  PushFront(21, root_node_ptr);
  Print(root_node_ptr);
  Delete(root_node_ptr);
  delete root_node_ptr;
  return 0;
}
