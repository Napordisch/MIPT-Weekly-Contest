#include <climits>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

struct Edge {
  uint32_t to = 0;
  uint32_t weight = 0;
};

class Graph {
 public:
  explicit Graph(uint32_t vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    visited_ = new bool[vertexes_amount_];
    graph_ = new vector<Edge>[vertexes_amount_];
  }

  ~Graph() {
    delete[] graph_;
    delete[] visited_;
  }

  void AddEdge(uint32_t x, uint32_t y, uint32_t weight) {
    Edge new_edge;
    new_edge.to = y - 1;
    new_edge.weight = weight;
    graph_[x - 1].push_back(new_edge);
    if (weight > k_) {  // updating max weight
      k_ = weight;
    }
  }

  vector<Edge> &GetChildren(uint32_t vertex) {
    vertex--;
    return graph_[vertex];
  }

  void Display() {
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      uint32_t size = graph_[i].size();
      cout << "[" << i + 1 << "]: ";
      for (uint32_t j = 0; j < size; ++j) {
        cout << graph_[i][j].to + 1 << "(weight: " << graph_[i][j].weight << ")"
             << " ";
      }
      cout << "\n";
    }
  }

  uint32_t VertexesAmount() {
    return vertexes_amount_;
  }

  void KBFS(uint32_t start, uint32_t end) {
    start--;
    end--;
    auto dist = new uint32_t[vertexes_amount_];
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      dist[i] = UINT32_MAX;
    }
    auto queues = new queue<uint32_t>[vertexes_amount_ * k_];
    queues[0].push(start);
    dist[start] = 0;

    for (uint32_t d = 0; d < vertexes_amount_ * k_; ++d) {
      while (!queues[d].empty()) {
        uint32_t v = queues[d].front();
        queues[d].pop();

        if (dist[v] < d) {
          continue;
        }

        vector<Edge> &neighbours = graph_[v];
        uint32_t size = neighbours.size();

        for (uint32_t i = 0; i < size; ++i) {
          Edge &to = neighbours[i];
          if (dist[to.to] > dist[v] + to.weight) {
            dist[to.to] = dist[v] + to.weight;
            queues[dist[to.to]].push(to.to);
          }
        }
      }
    }

    uint32_t the_dist = dist[end];
    if (the_dist != UINT32_MAX) {
      cout << dist[end] << "\n";
    } else {
      cout << -1 << "\n";
    }

    delete[] dist;
    delete[] queues;
  }

 private:
  vector<Edge> *graph_ = nullptr;
  uint32_t vertexes_amount_ = 0;
  bool *visited_ = nullptr;
  uint32_t k_ = 0;  // max weight
};

int main() {
  uint32_t n = 0;
  uint32_t m = 0;
  uint32_t s = 0;
  uint32_t f = 0;
  cin >> n >> m;
  if (m == 0) {
    cout << -1 << "\n";
    return 0;
  }
  cin >> s >> f;
  Graph g(n);
  for (uint32_t i = 0; i < m; ++i) {
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t t = 0;
    cin >> a >> b >> t;
    g.AddEdge(a, b, t);
  }
  g.KBFS(s, f);
  return 0;
}