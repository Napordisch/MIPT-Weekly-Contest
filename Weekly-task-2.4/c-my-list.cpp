#include <cstdint>
#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::list;

struct Node {
  uint32_t val;
  Node *next = nullptr;
  Node *prev = nullptr;
};

class List {
 public:
  Node *root = nullptr;

  uint32_t Size() {
    return size_;
  }

  uint32_t Front() {
    return root->val;
  }

  bool Empty() {
    return root == nullptr;
  }

  void Clear() {
    size_ = 0;
    while (root != nullptr) {
      Node *next = root->next;
      delete root;
      root = next;
    }
  }

  ~List() {
    Clear();
  }

  void PushFront(uint32_t key) {
    size_++;
    if (this->root == nullptr) {
      this->root = new Node;
      this->root->val = key;
      return;
    }
    Node *new_node = new Node;
    new_node->val = key;
    this->root->prev = new_node;
    new_node->next = this->root;
    this->root = new_node;
  }

  void PushBack(uint32_t key) {
    size_++;
    Node *new_node = new Node;
    new_node->val = key;
    Node *runner = this->root;
    if (runner == nullptr) {
      runner = new_node;
    }
    while (runner->next != nullptr) {
      runner = runner->next;
    }
    runner->next = new_node;
    new_node->prev = runner;
  }

  uint32_t Back() {
    Node *runner = root;
    while (runner->next != nullptr) {
      runner = runner->next;
    }
    return runner->val;
  }

  uint32_t PopBack() {
    size_--;
    uint32_t value = 0;
    Node *runner = this->root;
    if (runner->next == nullptr) {
      value = runner->val;
      delete runner;
      this->root = nullptr;
      return value;
    }
    while (runner->next->next != nullptr) {
      runner = runner->next;
    }
    value = runner->next->val;
    delete runner->next;
    runner->next = nullptr;
    return value;
  }

  uint32_t PopFront() {
    size_--;
    Node *new_root = nullptr;
    uint32_t value = this->root->val;
    if (this->root->next != nullptr) {
      new_root = this->root->next;
      new_root->prev = nullptr;
    }
    delete this->root;
    this->root = new_root;
    return value;
  }

  void PutAfter(size_t index, uint32_t value) {
    size_++;
    Node *runner = this->root;
    size_t current_index = 0;
    while (current_index != index) {
      runner = runner->next;
    }
    Node *new_node = new Node;
    new_node->val = value;
    new_node->next = runner->next;
    new_node->prev = runner;
    runner->next = new_node;
  }

 private:
  uint32_t size_ = 0;
};

class Graph {
 public:
  void Euler(uint32_t vertex) {
    for (uint32_t p = 0; p < vertexes_amount_; ++p) {
      while (table_[vertex][p] > 0) {
        table_[vertex][p]--;
        Euler(p);
      }
    }
    euler_path_.PushFront(vertex);
  }

  uint32_t AmountOfVertexes() {
    return vertexes_amount_;
  }

  explicit Graph(uint32_t vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    table_ = new uint32_t *[vertexes_amount_];
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      table_[i] = new uint32_t[vertexes_amount_];
    }
  }

  ~Graph() {
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      delete[] table_[i];
    }
    delete[] table_;
  }

  void IncreaseEdge(uint32_t from, uint32_t to) {
    if (table_[from - 1][to - 1] == 0) {
      edges_amount_++;
    }
    table_[from - 1][to - 1]++;
  }

  void DisplayTable() {
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      for (uint32_t j = 0; j < vertexes_amount_; ++j) {
        cout << table_[i][j] << " ";
      }
      cout << "\n";
    }
  }

  void DisplayEdges() {
    cout << vertexes_amount_ << " " << edges_amount_ << "\n";
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      for (uint32_t j = 0; j < vertexes_amount_; ++j) {
        if (table_[i][j] > 0) {
          cout << i + 1 << " " << j + 1 << " " << table_[i][j] << "\n";
        }
      }
    }
  }

  void DisplayEulerPath() {
    while (!euler_path_.Empty()) {
      cout << euler_path_.Front() + 1 << " ";
      euler_path_.PopFront();
    }
  }

  void ShowEulerPath() {
    if (!euler_path_.Empty()) {
      euler_path_.Clear();
    }
    Euler(0);
    cout << euler_path_.Size() << " ";
    DisplayEulerPath();
  }

 private:
  List euler_path_;
  uint32_t **table_ = nullptr;
  uint32_t vertexes_amount_ = 0;
  uint32_t edges_amount_ = 0;
};

int main() {
  uint32_t n = 0;
  uint32_t m = 0;
  cin >> n >> m;

  Graph city(m);
  for (uint32_t i = 0; i < n; ++i) {
    uint32_t route_elements_amount = 0;
    cin >> route_elements_amount;
    List points;
    for (uint32_t j = 0; j < route_elements_amount + 1; ++j) {
      uint32_t point = 0;
      cin >> point;
      points.PushBack(point);
      if (points.Size() == 2) {
        city.IncreaseEdge(points.Front(), points.Back());
        points.PopFront();
      }
    }
  }
  city.ShowEulerPath();
}