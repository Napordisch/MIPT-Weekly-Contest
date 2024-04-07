#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int dijkstra(vector<vector<int>>& graph, int source, int target) {
  int n = graph.size();
  vector<int> dist(n, INF);
  dist[source] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, source});

  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();

    if (d > dist[u]) continue;

    for (int v = 0; v < n; ++v) {
      if (graph[u][v] != -1) {
        int new_dist = dist[u] + graph[u][v];
        if (new_dist < dist[v]) {
          dist[v] = new_dist;
          pq.push({new_dist, v});
        }
      }
    }
  }

  return dist[target] == INF ? -1 : dist[target];
}

int main() {
  int N, s, t;
  cin >> N >> s >> t;

  vector<vector<int>> graph(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> graph[i][j];
    }
  }

  int shortest_path_length = dijkstra(graph, s, t);
  cout << shortest_path_length << endl;

  return 0;
}

