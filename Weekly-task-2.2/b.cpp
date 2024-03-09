#include <iostream>

using std::cin;
using std::cout;

struct Node {
  uint16_t vertex;
  Node* prev = nullptr;
  Node* next = nullptr;
};

class List {
 public:
  void PushFront(uint16_t vertex) {
    auto* new_node = new Node;
    new_node->vertex = vertex;
    new_node->next = root_;
    if (root_ != nullptr) {
      root_->prev = new_node;
    }
    root_ = new_node;
    amount_of_neighbours++;
  }
  bool Find(uint16_t vertex) {
    Node* runner = root_;
    while (runner != nullptr) {
      if (runner->vertex == vertex) {
        return true;
      }
      runner = runner->next;
    }
    return false;
  }
  ~List() {
    while (root_ != nullptr) {
      Node* to_dispose = root_;
      root_ = root_->next;
      delete to_dispose;
    }
  }
  uint16_t amount_of_neighbours = 0;

 private:
  Node* root_ = nullptr;
};

int main() {
  uint16_t amount_of_vertexes = 0;
  cin >> amount_of_vertexes;
  uint16_t amount_of_edges = 0;
  cin >> amount_of_edges;
  auto* neighbours = new List[amount_of_vertexes];

  for (uint16_t i = 0; i < amount_of_edges; i++) {
    uint16_t first = 0;
    uint16_t second = 0;
    cin >> first >> second;
    neighbours[first - 1].PushFront(second - 1);
    neighbours[second - 1].PushFront(first - 1);
  }
  for (uint16_t i = 0; i < amount_of_vertexes; i++) {
    cout << neighbours[i].amount_of_neighbours << " ";
  }
  delete[] neighbours;
}
