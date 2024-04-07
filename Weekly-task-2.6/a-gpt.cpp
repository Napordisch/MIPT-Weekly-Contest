#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::cin;
using std::cout;

using std::greater;
using std::pair;
using std::priority_queue;
using std::vector;

const int kInf = INT_MAX;

int Dijkstra(vector<vector<int>>& graph, int source, int target) {
  int n = static_cast<int>(graph.size());
  vector<int> dist(n, kInf);
  dist[source] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.emplace(0, source);

  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();

    if (d > dist[u]) {
      continue;
    }

    for (int v = 0; v < n; ++v) {
      if (graph[u][v] != -1) {
        int new_dist = dist[u] + graph[u][v];
        if (new_dist < dist[v]) {
          dist[v] = new_dist;
          pq.emplace(new_dist, v);
        }
      }
    }
  }

  return dist[target] == kInf ? -1 : dist[target];
}

int main() {
  int n = 0;
  int s = 0;
  int t = 0;
  cin >> n >> s >> t;

  vector<vector<int>> graph(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> graph[i][j];
    }
  }

  int shortest_path_length = Dijkstra(graph, s, t);
  cout << shortest_path_length << '\n';

  return 0;
}
