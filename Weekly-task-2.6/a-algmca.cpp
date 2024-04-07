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
  vector<int> d(n, INT_MAX);
  d[s] = 0;
  std::priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
  q.emplace(0, s);
  while (!q.empty()) {
    auto [cur_d, v] = q.top();
    q.pop();
    if (used[v]) {
      continue;
    }
    used[v] = true;
    if (cur_d > d[v]) {
      continue;
    }
    for (int u = 0; u < n; ++u) {
      int w = graph[v][u];
      if (d[u] > d[v] + w) {
        d[u] = d[v] + w;
        q.emplace(d[u], u);
      }
    }
  }

  if (d[t] == INT_MAX) {
    cout << -1;
  } else {
    cout << d[t];
  }
}
