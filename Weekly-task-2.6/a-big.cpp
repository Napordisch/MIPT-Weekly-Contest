#include <cstdint>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::vector;

template <typename T>
void Display2DVector(vector<vector<T>> the_vector) {
  for (int64_t i = 0; i < the_vector.size(); ++i) {
    for (int64_t vertex : the_vector[i]) {
      cout << vertex << ' ';
    }
    cout << '\n';
  }
}

int main() {
  int64_t n = 0;
  int64_t s = 0;  // from
  int64_t t = 0;  // to
  cin >> n >> s >> t;
  s--;
  t--;

  vector<vector<int64_t>> graph(n, vector<int64_t>(n));
  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < n; ++j) {
      cin >> graph[i][j];
    }
  }

  // Dijkstra
  vector<int64_t> distances(n, INT64_MAX);
  distances[s] = 0;
  std::priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>, std::greater<pair<int64_t, int64_t>>> q;

  q.emplace(0, s);

  while (!q.empty()) {
    auto [current_distance, vertex] = q.top();
    q.pop();
    if (current_distance > distances[vertex]) {
      continue;
    }
    for (int64_t u = 0; u < n; ++u) {
      if (graph[vertex][u] == -1 || u == vertex) {
        continue;
      }
      int64_t new_distance = distances[vertex] + graph[vertex][u];
      if (distances[u] > new_distance) {
        distances[u] = new_distance;
        q.emplace(distances[u], u);
      }
    }
  }

  if (distances[t] == INT64_MAX) {
    cout << -1;
  } else {
    cout << distances[t];
  }
}
