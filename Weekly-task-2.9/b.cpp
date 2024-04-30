#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Edge{
  Edge(int id, int w) {
    index = id;
    capacity = w;
  }
  int index = 0;
  int capacity = 0;
};

class Graph {
 public:
  Graph(int amount_of_middle_vertexes, int amount_of_middle_edges) {
    vertexes_amount_ = (2 * amount_of_middle_vertexes) + 2;
    middle_edges_amount_ = amount_of_middle_edges;
    adjacency_list_.resize(vertexes_amount_);
  }
  void AddEdge(from, to, capacity) {
    adjacency_list_[from].emplace_back(to, capacity);
  }


 private:
  vector<vector<int>> adjacency_list_;
  int vertexes_amount_ = 0;
  int middle_edges_amount_ = 0;
};

int main() {
  // source is a vertex 0 target is a vertex 2n + 1
  int n = 0;
  int m = 0;
  Graph g(n, m);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    int capacity = 0;
    cin >> capacity;
    g.AddEdge(0, 1, capacity);
  }
  for (int i = 1; i <= n; ++i) {
    int target_vertex = 2 * n;
    int capacity = 0;
    cin >> capacity;
    g.AddEdge(n + i, target_vertex, capacity);
  }
  return 0;
}
