#include <iostream>
#include <climits>
#include <vector>
#include <cstdint>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
  Edge() = default;
  Edge(uint16_t f, uint16_t t, int16_t w) {
    from = f;
    to = t;
    weight = w;
  }
  uint16_t from = 0;
  uint16_t to = 0;
  int16_t weight = 0;
};

void FordBellman(vector<int> &distances, uint16_t n, vector<Edge> edges) {
  uint16_t start = 0;
  distances[start] = 0;
  for (uint16_t i = 1; i < n; ++i) {
    uint16_t amount_of_edges = edges.size();
    for (uint16_t e = 0; e < amount_of_edges; ++e) {
      uint16_t from = edges[e].from;
      uint16_t to = edges[e].to;
      int16_t weight = edges[e].weight;
      if (distances[to] > distances[from] + weight && distances[from] != INT_MAX) {
        distances[to] = distances[from] + weight;
      }
    }
  }
}

int main() {
  uint16_t n = 0;
  uint16_t m = 0;
  cin >> n >> m;
  vector<Edge> edges(m);

  for (uint16_t i = 0; i < m; ++i) {
    uint16_t from = 0;
    uint16_t to = 0;
    int16_t weight = 0;
    cin >> from >> to;
    cin >> weight;
    edges[i] = Edge(from - 1, to - 1, weight);
  }

  vector<int> distances(n, INT_MAX);
  FordBellman(distances, n, edges);
  for (uint16_t i = 0; i < n; ++i) {
    if (distances[i] == INT_MAX) {
      cout << 30000 << ' ';
      continue;
    }
    cout << distances[i] << ' ';
  }

  return 0;
}
