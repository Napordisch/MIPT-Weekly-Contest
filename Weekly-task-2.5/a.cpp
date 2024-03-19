#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;


class Graph {
 public:

  Graph(uint32_t vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    visited_ = new bool[vertexes_amount_];
    graph_ = new vector<uint32_t>[vertexes_amount_];
  }

  ~Graph() {
    delete[] graph_;
    delete[] visited_;
  }

  void AddEdge(uint32_t x, uint32_t y) { // graph is not oriented
    graph_[x - 1].push_back(y - 1);
    graph_[y - 1].push_back(x - 1);
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

 private:
  vector<uint32_t>* graph_ = nullptr;
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
  g.Display();

  return 0;
}
