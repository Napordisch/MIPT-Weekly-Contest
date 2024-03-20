#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class Node {
 public:
  explicit Node(uint32_t value) {
    vertex = value;
  }
  uint32_t vertex = 0;
  Node *next = nullptr;
  Node *previous = nullptr;
};

class ListQueue {
 public:
  void Push(uint32_t value) {
    PushBack(value);
  }

  uint32_t Pop() {
    return PopFront();
  }

  uint32_t Top() {
    return Front();
  }

  bool IsEmpty() {
    return root_ == nullptr;
  }

  void PushFront(uint32_t value) {
    Node *new_node = new Node(value);
    new_node->next = root_;
    if (root_ != nullptr) {
      root_->previous = new_node;
    }
    root_ = new_node;
  }

  uint32_t PopFront() {
    if (root_ == nullptr) {
      cout << "empty queue"
           << "\n";
      return 0;
    }
    uint32_t value = root_->vertex;
    Node *new_root = root_->next;
    delete root_;
    root_ = new_root;
    if (root_ != nullptr) {
      root_->previous = nullptr;
    }
    return value;
  }

  uint32_t PopBack() {
    Node *runner = root_;
    if (runner == nullptr) {
      cout << "empty queue"
           << "\n";
      return 0;
    }
    while (runner->next != nullptr) {
      runner = runner->next;
    }
    Node *new_back = runner->previous;
    if (new_back != nullptr) {
      new_back->next = nullptr;
    }
    uint32_t value = runner->vertex;
    delete runner;
    return value;
  }

  uint32_t Back() {
    Node *runner = root_;
    if (runner == nullptr) {
      cout << "empty queue"
           << "\n";
      return 0;
    }
    while (runner->next != nullptr) {
      runner = runner->next;
    }
    uint32_t value = runner->vertex;
    return value;
  }

  void PushBack(uint32_t value) {
    Node *new_node = new Node(value);
    if (root_ == nullptr) {
      root_ = new_node;
      return;
    }
    Node *runner = root_;
    while (runner->next != nullptr) {
      runner = runner->next;
    }
    runner->next = new_node;
    new_node->previous = runner;
  }

  uint32_t Front() {
    return root_->vertex;
  }

  ~ListQueue() {
    while (root_ != nullptr) {
      PopFront();
    }
  }

 private:
  Node *root_ = nullptr;
};

class Graph {
 public:
  explicit Graph(uint32_t vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    visited_ = new bool[vertexes_amount_];
    graph_ = new vector<uint32_t>[vertexes_amount_];
  }

  ~Graph() {
    delete[] graph_;
    delete[] visited_;
  }

  void AddEdge(uint32_t x, uint32_t y) {  // graph is not oriented
    graph_[x - 1].push_back(y - 1);
    graph_[y - 1].push_back(x - 1);
  }

  vector<uint32_t> &GetChildren(uint32_t vertex) {
    vertex--;
    return graph_[vertex];
  }

  void BFS(uint32_t start, uint32_t destination) {
    start--;
    destination--;
    auto distances = new uint32_t[vertexes_amount_];
    auto prev = new uint32_t[vertexes_amount_];
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      distances[i] = INT_MAX;
      prev[i] = INT_MAX;
    }
    distances[start] = 0;
    ListQueue q;

    q.Push(start);
    while (!q.IsEmpty()) {
      uint32_t v = q.Pop();
      vector<uint32_t> &children = graph_[v];
      uint32_t size = children.size();
      for (uint32_t i = 0; i < size; ++i) {
        uint32_t to = children[i];
        if (distances[to] == INT_MAX) {
          distances[to] = distances[v] + 1;
          q.Push(to);
          prev[to] = v;
        }
      }
    }

    uint32_t index = destination;
    ListQueue path_list;
    path_list.PushFront(index);
    while (prev[index] != INT_MAX) {
      path_list.PushFront(prev[index]);
      index = prev[index];
    }

    if (distances[destination] == INT_MAX) {
      path_list.PopFront();
      cout << "-1"
           << "\n";
    } else {
      cout << distances[destination] << "\n";
    }
    while (!path_list.IsEmpty()) {
      cout << path_list.PopFront() + 1 << " ";
    }

    delete[] distances;
    delete[] prev;
  }

  void Display() {
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      uint32_t size = graph_[i].size();
      cout << "[" << i + 1 << "]: ";
      for (uint32_t j = 0; j < size; ++j) {
        cout << graph_[i][j] + 1 << " ";
      }
      cout << "\n";
    }
  }
  uint32_t VertexesAmount() {
    return vertexes_amount_;
  }

 private:
  vector<uint32_t> *graph_ = nullptr;
  uint32_t vertexes_amount_ = 0;
  bool *visited_ = nullptr;
};

int main() {
  uint32_t n = 0;
  uint32_t m = 0;
  uint32_t a = 0;
  uint32_t b = 0;
  cin >> n >> m;
  cin >> a >> b;
  Graph g(n);
  for (uint32_t i = 0; i < m; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    g.AddEdge(from, to);
  }
  g.BFS(a, b);

  return 0;
}
