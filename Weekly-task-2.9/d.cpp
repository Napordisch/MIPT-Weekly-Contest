#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
  Edge(int t, int w) {
    to = t;
    weight = w;
  }

  unsigned int to = 0;
  int weight = 0;
};

struct Graph {
  Graph(unsigned int n, unsigned int m, bool d) {
    vertexes_amount = n;
    edges_amount = m;
    adjacency_list.resize(vertexes_amount);
    directed = d;
  }

  void AddEdge(unsigned int from, unsigned int to, int weight) {
    adjacency_list[from - 1].emplace_back(to - 1, weight);
    if (!directed) {
      adjacency_list[to - 1].emplace_back(from - 1, weight);
    }
  }

  void DisplayNeighbours() {
    for (unsigned int i = 0; i < adjacency_list.size(); ++i) {
      cout << i + 1 << ':' << ' ';
      const vector<Edge> &neighbours = adjacency_list[i];
      for (const Edge &neighbour : neighbours) {
        cout << neighbour.to + 1 << ',' << neighbour.weight << ' ';
      }
      cout << '\n';
    }
  }

  void BFS(unsigned int start) {
    cout << '\n';
    std::queue<int> to_visit;
    std::vector<bool> visited(vertexes_amount, false);
    visited[start] = true;
    to_visit.push(start);
    while (!to_visit.empty()) {
      unsigned int v = to_visit.front();
      to_visit.pop();
      cout << v + 1 << ' ';
      for (const Edge &current_edge : adjacency_list[v]) {
        unsigned int current_vertex = current_edge.to;
        if (!visited[current_vertex]) {
          visited[current_vertex] = true;
          to_visit.push(current_vertex);
        }
      }
    }
    cout << '\n';
  }

  unsigned int vertexes_amount = 0;
  unsigned int edges_amount = 0;

  vector<vector<Edge>> adjacency_list;

  bool directed = false;
};

void Solve() {
  unsigned int n = 0;
  unsigned int m = 0;
  cin >> n >> m;
  Graph g(n, m, true);
  for (unsigned int i = 0; i < m; ++i) {
    unsigned int from = 0;
    unsigned int to = 0;
    unsigned int weight = 0;
    cin >> from >> to >> weight;
    g.AddEdge(from, to, weight);
  }
  g.BFS(0);
}

int main() {
  Solve();
  return 0;
}
