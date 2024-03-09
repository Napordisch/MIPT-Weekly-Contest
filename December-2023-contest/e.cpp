#include <iostream>

using std::cin;
using std::cout;
using std::string;

struct Node{
  int index;
  Node* next = nullptr;
  Node* prev = nullptr;
};

void PushBack(Node *&root, int value) {
  Node* runner = root; 
  Node* cur_prev = runner;
  while (runner != nullptr) {
    cur_prev = runner;
    runner = runner->next;
  }
  Node *new_node = new Node;
  new_node->index = value;
  runner = new_node;
  if (cur_prev != nullptr) {
    cur_prev->next = runner;
  }
  runner->prev = cur_prev;
  if (root == nullptr) {
    root = runner;
  }
}

int PopFront(Node *&root){
  int root_value = root->index;
  root = root->next;
  delete root;
  return root_value;
}

// int main() {
//   string input;
//   cin >> input;
//   int o_curlies = 0;
//   int o_sqares = 0;
//   int o_brackets = 0;
//   int c_curlies = 0;
//   int c_sqares = 0;
//   int c_brackets = 0;
//   int len = input.length();
//   for (int i = 0; i < len; i++) {
//     if input[i] == '{' {
//       o_curlies++;
//     }
//     if input[i] == '}' {
//       c_curlies++;
//     }
//     if input[i] == '(' {
//       o_brackets++;
//     }
//     if input[i] == ')' {
//       c_brackets++;
//     }
//     if input[i] == '[' {
//       o_sqares++;
//     }
//     if input[i] == ']' {
//       c_sqares++;
//       if (c_squares - o_sqares != 0) {
//         cout << i + 1;
//       }
//     }
//   }
//   return 0;
// }

int main() {
  Node *root = nullptr;
  PushBack(root, 2);
  PushBack(root, 3);
  PushBack(root, 5);
  PushBack(root, 6);
  cout << PopFront(root);
  cout << PopFront(root);
  cout << PopFront(root);
  cout << PopFront(root);
  return 0;
}