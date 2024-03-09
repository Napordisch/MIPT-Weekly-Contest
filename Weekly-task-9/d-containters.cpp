#include <iostream>

struct Node {
  int32_t value;
  Node* next = nullptr;
  Node* prev = nullptr;
};

struct Amove {
  int32_t from;
  int32_t to;
  Amove* prev = nullptr;
};

void NewMove(Amove*& last_move, int32_t from, int32_t to){
  auto* new_move = new Amove;
  new_move->from = from + 1;
  new_move->to = to + 1;
  new_move->prev = last_move;
  last_move = new_move;
}

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
  if (root != nullptr){
    root->prev = nullptr;
  }
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

void Add(int32_t new_value, Node*& previous) {
  auto* new_node = new Node;
  new_node->value = new_value;
  new_node->next = previous->next;
  new_node->next->prev = new_node;
  previous->next = new_node;
  new_node->prev = previous;
}

void Remove(Node*& current) {
  current->prev->next = current->next;
  current->next->prev = current->prev;
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

void Delete(Amove*& root) {
  Amove* runner = root;
  while (runner != nullptr) {
    Amove* prev = runner->prev;
    delete runner;
    runner = prev;
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

void Front(Node* root) {
  Node* runner = root;
  while (runner->next != nullptr) {
    runner = runner->next;
  }
  std::cout << runner->value << "\n";
}

void Move(Node*& cur_root, int32_t to, Node**& stacks, Amove*& last_move, int32_t from) {
  if (cur_root == nullptr) {
    // Handle the case when pointers are null
    return;
  }
  NewMove(last_move, from, to);
  PushFront(cur_root->value, stacks[to]);
  PopFront(cur_root);
}

int main() {
  Amove* last_move = new Amove;
  using std::cin;
  using std::cout;
  uint32_t n;
  cin >> n;

  auto** stacks = new Node*[n];

  for (uint32_t i = 0; i < n; i++) {
    stacks[i] = nullptr;
  }

  // making the initial stacks
  for (uint32_t i = 0; i < n; i++) {
    uint32_t k;
    cin >> k;
    for (uint32_t j = 0; j < k; j++) {
      uint32_t container;
      cin >> container;
      PushFront(container, stacks[i]);
    }
  }

  for (uint32_t i = 0; i < n; i++) { // looping through stacks
    Node* cur_node = stacks[i];
    Node* cur_root = stacks[i];
    while (true) {
      if (cur_node == nullptr) {
        break;
      }
      if (cur_node->value == i + 1) {
        if (cur_node->next != nullptr) { // if there is next
          std::cout << "next";
          cur_node = cur_node->next; 
          continue;
        } else{
          break;
        }
      }

      uint32_t dumped = 0; // amount of dumped containers
      uint32_t dump; // temp dump stack number
      if (cur_node != cur_root) {
        if (n < 3) {
          cout << 0 << "\n";

          Delete(last_move);
          for (uint32_t y = 0; y < n; y++) {
            Delete(stacks[y]);
          }
          delete[] stacks;
          delete last_move;
          return 0;
        }
        // choosing dump/buffer stack number
        for (uint32_t j = 0; j < n; j++) {
          if (j != i && j != cur_node->value - 1) {
            dump = j;
            break;
          }
        }
        // dumping
        while (cur_node != cur_root) {
          Move(cur_root, dump, stacks, last_move, i);
          dumped++;
        }
      }

      // std::cout << "moved";
      Move(cur_root, cur_root->value - 1, stacks, last_move, i);

      if (dumped > 0) {
        for (uint32_t j = 0; j < dumped; j++) {
          Move(stacks[dump], i, stacks, last_move, dump);
        }

      }
    }
  }

  Delete(last_move);
  for (uint32_t y = 0; y < n; y++) {
    Delete(stacks[y]);
  }
  delete[] stacks;
  delete last_move;
  return 0;
}