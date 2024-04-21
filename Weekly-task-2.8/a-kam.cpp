#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool DFS(int u, int n, vector<vector<int>> &g, vector<bool> &visited,
         vector<int> &matching) {
  if (visited[u]) {
    return false;
  }

  visited[u] = true;
  for (auto v : g[u]) {
    if (visited[n + v]) {
      continue;
    }

    visited[n + v] = true;

    if (matching[v] == -1) {
      matching[v] = u;
      return true;
    }
    int w = matching[v];
    bool dfs_res = DFS(w, n, g, visited, matching);
    if (dfs_res) {
      matching[v] = u;
      return true;
    }
  }

  return false;
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<vector<int>> g(n);

  for (int u = 0; u < n; u++) {
    int v = -1;
    cin >> v;

    while (v != 0) {
      g[u].push_back(v - 1);
      cin >> v;
    }
  }

  vector<int> matching(m, -1);

  int matches_count = 0;
  for (int i = 0; i < n; i++) {
    vector<bool> visited(n + m, false);
    bool result = DFS(i, n, g, visited, matching);
    if (result) {
      ++matches_count;
    }
  }

  cout << matches_count << '\n';
  for (int v = 0; v < m; v++) {
    if (matching[v] != -1) {
      cout << matching[v] + 1 << ' ' << v + 1 << '\n';
    }
  }
}
