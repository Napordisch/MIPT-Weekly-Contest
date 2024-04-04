#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::min;
using std::vector;

void DisplayTable(vector<vector<int>> table) {
  for (unsigned int i = 0; i < table.size(); ++i) {
    for (unsigned int j = 0; j < table[i].size(); ++j) {
      cout << table[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  unsigned int n = 0;
  cin >> n;

  vector<vector<int>> graph_table(n, vector<int>(n));

  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      int weight = 0;
      cin >> weight;
      if (i != j && weight == 0) {
        weight = INT16_MAX;
      }
      graph_table[i][j] = weight;
    }
  }

  vector<vector<int>> distances(graph_table);

  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int from = 0; from < n; ++from) {
      for (unsigned int to = 0; to < n; ++to) {
        int new_distance = distances[from][i] + distances[i][to];
        if (new_distance < distances[from][to]) {
          distances[from][to] = new_distance;
        }
      }
    }
  }

  DisplayTable(distances);
}