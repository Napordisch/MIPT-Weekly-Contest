#include <iostream>

using std::cin;
using std::cout;

int FloydWarshall(Graph the_graph) {
  uint16_t **dists = new uint16_t*[the_graph.size];
  for (uint16_t i = 0; i < the_graph.size; ++i) {
    dists[i] = new uint16_t[the_graph.size];
  }
  for (uint16_t u = 0; u < the_graph.size; ++u) {
    for (uint16_t v = 0; v < the_graph.size; ++v) {
      dists[u][v] = the_graph.table[u][v];
    }
  }
}

struct Graph {
  int16_t size = 0;

  Graph(int n) {
    size = n;
    table = new uint16_t*[size];
    for (uint16_t i = 0; i < size; ++i) {
      table[i] = new uint16_t[size];
    }
  }

  uint16_t **table = nullptr;

  void FillFromInputTable() {
    for (uint16_t i = 0; i < size; ++i) {
      for (uint16_t j = 0; j < size; ++j) {
        cin >> table[i][j];
      }
    }
  }
  void Display() {
    for (uint16_t i = 0; i < size; ++i) {
      for (uint16_t j = 0; j < size; ++j) {
        cout << table[i][j] << " ";
      }
      cout << "\n";
    }
  }

  ~Graph() {
    for (uint16_t i = 0; i < size; ++i) {
      delete[] table[i];
    }
    delete[] table;
  }
};

int main() {
  uint16_t n = 0;
  cin >> n;
  Graph g(n);
  g.FillFromInputTable();
  return 0;
}