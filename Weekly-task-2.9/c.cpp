#include <limits>
#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
  Edge(int t, int64_t w) {
    to = t;
    weight = w;
  }

  uint64_t to = 0;
  int64_t weight = 0;
};

struct Graph {
  Graph(uint64_t n, uint64_t m, bool d) {
    vertexes_amount = n;
    edges_amount = m;
    adjacency_table.resize(vertexes_amount, vector<int64_t>(vertexes_amount, 0));
    directed = d;
  }

  void AddEdge(uint64_t from, uint64_t to, int64_t weight) {
    adjacency_table[from - 1][to - 1] += weight;
    if (!directed) {
      adjacency_table[to - 1][from - 1] += weight;
    }
  }

  void DisplayTable() {
    for (const vector<int64_t> &neighbours : adjacency_table) {
      for (const int64_t &vertex_weight : neighbours) {
        cout << vertex_weight << ' ';
      }
      cout << '\n';
    }
  }

  bool BFS(uint64_t start, uint64_t target, vector<uint64_t> &parents) {
    std::queue<uint64_t> to_visit;
    std::vector<bool> visited(vertexes_amount, false);
    visited[start] = true;
    to_visit.push(start);
    parents.resize(vertexes_amount, -1);
    while (!to_visit.empty()) {
      uint64_t v = to_visit.front();
      to_visit.pop();
      for (uint64_t current_vertex = 0; current_vertex < vertexes_amount; ++current_vertex) {
        if (adjacency_table[v][current_vertex] == 0) {
          continue;
        }

        if (!visited[current_vertex] && ResidualCapacity(v, current_vertex) > 0) {
          visited[current_vertex] = true;
          parents[current_vertex] = v;

          if (current_vertex == target) {
            return true;
          }

          to_visit.push(current_vertex);
        }
      }
    }
    return false;
  }

  uint64_t EdmondsKarp(uint64_t source, uint64_t target) {
    uint64_t max_flow = 0;
    flows.resize(vertexes_amount, vector<int64_t>(vertexes_amount, 0));
    vector<uint64_t> parents(vertexes_amount, -1);
    while (BFS(source, target, parents)) {
      int64_t path_residual_capacity = std::numeric_limits<int64_t>::max();

      uint64_t path_element = target;

      while (path_element != source) {
        int64_t new_residual_capacity = ResidualCapacity(parents[path_element], path_element);
        if (path_residual_capacity > new_residual_capacity) {
          path_residual_capacity = new_residual_capacity;
        }
        path_element = parents[path_element];
      }

      path_element = target;
      while (path_element != source) {
        flows[parents[path_element]][path_element] += path_residual_capacity;
        flows[path_element][parents[path_element]] = -flows[parents[path_element]][path_element];
        path_element = parents[path_element];
      }

      max_flow += path_residual_capacity;
    }
    return max_flow;
  }

  int64_t ResidualCapacity(uint64_t u, uint64_t v) {
    return adjacency_table[u][v] - flows[u][v];
  }

  uint64_t vertexes_amount = 0;
  uint64_t edges_amount = 0;

  vector<vector<int64_t>> adjacency_table;
  vector<vector<int64_t>> flows;

  bool directed = false;
};

void Solve() {
  uint64_t n = 0;
  uint64_t m = 0;
  cin >> n >> m;
  Graph g(n, m, true);
  for (uint64_t i = 0; i < m; ++i) {
    uint64_t from = 0;
    uint64_t to = 0;
    int64_t weight = 0;
    cin >> from >> to >> weight;
    g.AddEdge(from, to, weight);
  }
  cout << g.EdmondsKarp(0, n - 1) << '\n';
}
void Test1() {
  Graph g(2, 1, true);
  g.AddEdge(1, 2, 0);
  cout << g.EdmondsKarp(0, 1) << '\n';
}

void Test2() {
  Graph g(500, 996, true);
  for (uint64_t i = 2; i <= 499; ++i) {
    g.AddEdge(1, i, 1000000000);
  }
  for (uint64_t i = 2; i <= 499; ++i) {
    g.AddEdge(i, 500, 1000000000);
  }
  cout << g.EdmondsKarp(0, 499) << '\n';
}

void Test3() {
  Graph g(2, 10000, true);
  for (uint64_t i = 0; i < 10000; ++i) {
    g.AddEdge(1, 2, 1000000000);
  }
  cout << g.EdmondsKarp(0, 1) << '\n';
}

int main() {
  Solve();
  return 0;
}
