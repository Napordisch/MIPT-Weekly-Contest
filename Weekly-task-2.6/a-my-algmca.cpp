#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::pair;
using std::vector;

template <typename T>
void Display2DVector(vector<vector<T>> the_vector) {
  for (int i = 0; i < the_vector.size(); ++i) {
    for (int vertex : the_vector[i]) {
      cout << vertex << ' ';
    }
    cout << '\n';
  }
}

int main() {
  int n = 0;
  int s = 0;  // from
  int t = 0;  // to
  cin >> n >> s >> t;
  s--;
  t--;

  vector<vector<int>> graph(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> graph[i][j];
    }
  }

  // Dijkstra
  vector<bool> used(n, false);
  vector<int> distances(n, INT_MAX);
  distances[s] = 0;
  std::set<pair<int, int>> q;

  q.insert({0, s});

  while (!q.empty()) {
    auto [current_distance, vertex] = *(q.begin());
    q.erase(q.begin());

    if (current_distance > distances[vertex]) {
      continue;
    }
    for (int u = 0; u < n; ++u) {
      if (graph[vertex][u] == -1 || u == vertex || used[u]) {
        continue;
      }
      int new_distance = distances[vertex] + graph[vertex][u];
      if (distances[u] > new_distance) {
        distances[u] = new_distance;
        q.insert({distances[u], u});
      }
    }
  }

  if (distances[t] == INT_MAX) {
    cout << -1;
  } else {
    cout << distances[t];
  }
}
