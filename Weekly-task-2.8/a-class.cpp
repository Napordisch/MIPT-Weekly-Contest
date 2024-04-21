#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using std::vector;

class Graph {
 public:
  Graph(int n, int m) {
    list_.resize(n);
    n_ = n;
    m_ = m;
  }
  void AddEdge(int from, int to) {
    list_[from - 1].push_back(to - 1);
  }

  bool DFS(int start) {
    if (used_[start]) {
      return false;
    }
    used_[start] = true;

    for (int v : list_[start]) {
      if (used_[n_ + v]) {
        continue;
      }
      used_[n_ + v] = true;

      if (matches_[v] == -1) {
        matches_[v] = start;
        return true;
      }
      bool dfs_res = DFS(matches_[v]);
      if (dfs_res) {
        matches_[v] = start;
        return true;
      }
    }
    return false;
  }

  int Kuhn() {
    int matches_count = 0;
    matches_.resize(m_, -1);
    for (int i = 0; i < n_; ++i) {
      used_.resize(n_ + m_, false);
      bool result = DFS(i);
      if (result) {
        ++matches_count;
      }
    }
    return matches_count;
  }

  void DisplayMatches() {
    for (int v = 0; v < m_; ++v) {
      if (matches_[v] != -1) {
        cout << matches_[v] + 1 << ' ' << v + 1 << '\n';
      }
    }
  }

 private:
  int n_ = 0;
  int m_ = 0;
  vector<vector<int>> list_;
  vector<bool> used_;
  vector<int> matches_;
};

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;

  Graph g(n, m);
  for (int u = 0; u < n; ++u) {
    int v = -1;
    cin >> v;
    while (v != 0) {
      g.AddEdge(u + 1, v);
      cin >> v;
    }
  }
  cout << g.Kuhn() << '\n';
  g.DisplayMatches();
  return 0;
}
