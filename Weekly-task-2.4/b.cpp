#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class Graph {
 public:
  uint16_t *states = nullptr;
  vector<uint32_t> *adjacency = nullptr;
  vector<uint32_t> priority;

  void TopSortDisplay() {
    for (uint32_t i = 0; i < priority.size(); ++i) {
      cout << priority[i] + 1 << " ";
    }
    cout << "\n";
  }

  void AddEdge(uint32_t from, uint32_t to) {
    adjacency[from - 1].push_back(to - 1);
  }
  Graph(uint32_t amount_of_vertexes, uint32_t amount_of_edges) {
    amount_of_vertexes_ = amount_of_vertexes;
    amount_of_edges_ = amount_of_edges;
    adjacency = new vector<uint32_t>[amount_of_vertexes_];
    states = new uint16_t[amount_of_vertexes_]{};
  }
  ~Graph() {
    delete[] states;
    delete[] adjacency;
  }
  void Display() {
    for (uint32_t i = 0; i < amount_of_vertexes_; ++i) {
      uint32_t size = adjacency[i].size();
      cout << "[" << i + 1 << "]: ";
      for (uint32_t j = 0; j < size; ++j) {
        cout << adjacency[i][j] + 1 << " ";
      }
      cout << "\n";
    }
  }

 private:
  uint32_t amount_of_edges_ = 0;
  uint32_t amount_of_vertexes_ = 0;
};

void DFS(uint32_t start, Graph &g, bool belonging = false, uint32_t *component_belonging = nullptr, uint32_t k = 0) {
  g.states[start] = 1;
  vector<uint32_t> &children = g.adjacency[start];
  uint32_t amount_of_children = children.size();

  for (uint32_t i = 0; i < amount_of_children; ++i) {
    if (g.states[children[i]] == 0) {
      DFS(children[i], g, belonging, component_belonging, k);
    }
  }

  g.states[start] = 2;
  if (belonging) {
    g.priority.push_back(start);
  } else {
    component_belonging[start] = k;
  }
}

int main() {
  uint32_t n = 0;
  uint32_t m = 0;
  cin >> n >> m;
  Graph g(n, m);
  Graph tg(n, m);

  for (uint32_t i = 0; i < m; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    if (from != 0 && to != 0) {
      g.AddEdge(from, to);
      tg.AddEdge(to, from);
    }
  }
  for (uint32_t i = 0; i < n; ++i) {
    if (g.states[i] == 0) {
      DFS(i, g, true);
    }
  }
  uint32_t components_amount = 0;

  auto component_belonging = new uint32_t[n];
  for (uint32_t i = 0; i < n; ++i) {
    uint32_t vertex_index = g.priority[n - i - 1];
    if (tg.states[vertex_index] == 0) {
      DFS(vertex_index, tg, false, component_belonging, components_amount);
      components_amount++;
    }
  }

  cout << components_amount << "\n";
  for (uint32_t i = 0; i < n; ++i) {
    cout << component_belonging[i] + 1 << " ";
  }

  delete[] component_belonging;
  return 0;
}
