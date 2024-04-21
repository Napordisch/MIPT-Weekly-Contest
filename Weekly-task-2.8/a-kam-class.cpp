#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class Graph {
 public:
  Graph(int n, int m) {
    n_ = n;
    m_ = m;
    list_.resize(n_);
  }

  void AddEdge(int from, int to) {
    list_[from].push_back(to - 1);  // from is 0-indexed to is 1-indexed
  }

  bool DFS(int u, vector<bool> &visited) {
    if (visited[u]) {
      return false;
    }

    visited[u] = true;
    for (auto v : list_[u]) {
      if (visited[n_ + v]) {
        continue;
      }

      visited[n_ + v] = true;

      if (matches_[v] == -1) {
        matches_[v] = u;
        return true;
      }
      int w = matches_[v];
      bool dfs_res = DFS(w, visited);
      if (dfs_res) {
        matches_[v] = u;
        return true;
      }
    }

    return false;
  }

  int Kuhn() {
    matches_.resize(m_, -1);
    int matches_count = 0;
    for (int i = 0; i < n_; ++i) {
      vector<bool> visited(n_ + m_, false);
      bool result = DFS(i, visited);
      if (result) {
        ++matches_count;
      }
    }
    return matches_count;
  }
  void DisplayMatches() {
    cout << Kuhn() << '\n';
    for (int v = 0; v < m_; v++) {
      if (matches_[v] != -1) {
        cout << matches_[v] + 1 << ' ' << v + 1 << '\n';
      }
    }
  }

 private:
  vector<vector<int>> list_;
  vector<int> matches_;
  int n_ = 0;
  int m_ = 0;
};

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  Graph g(n, m);

  for (int u = 0; u < n; u++) {
    int v = -1;
    cin >> v;

    while (v != 0) {
      g.AddEdge(u, v);
      cin >> v;
    }
  }

  g.DisplayMatches();
}
