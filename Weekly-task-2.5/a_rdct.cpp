#include <climits>
#include <cstdint>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
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
    queue<uint32_t> q;

    q.push(start);
    while (!q.empty()) {
      uint32_t v = q.front();
      q.pop();

      for (auto u : graph_[v]) {
        if (distances[u] == INT_MAX) {
          distances[u] = distances[v] + 1;
          q.push(u);
          prev[u] = v;
        }
      }
    }

    uint32_t index = destination;
    std::stack<uint32_t> path_list;
    path_list.push(index);
    while (prev[index] != INT_MAX) {
      path_list.push(prev[index]);
      index = prev[index];
    }

    if (distances[destination] == INT_MAX) {
      path_list.pop();
      cout << "-1"
           << "\n";
    } else {
      cout << distances[destination] << "\n";
    }
    while (!path_list.empty()) {
      cout << path_list.top() + 1 << " ";
      path_list.pop();
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
