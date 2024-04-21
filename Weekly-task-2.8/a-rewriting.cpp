#include <vector>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using std::vector;

using std::pair;

class Graph {
 public:
  Graph(int n, int m) {
    a_size_ = n;
    b_size_ = m;
    adjacency_list_.resize(n);
  }

  void AddEdge(int from, int to) {
    from--;
    to--;
    adjacency_list_[from].push_back(to);
  }

  void Display() {
    for (unsigned int i = 0; i < adjacency_list_.size(); ++i) {
      for (unsigned int j = 0; j < adjacency_list_[i].size(); ++j) {
        cout << adjacency_list_[i][j] + 1 << ' ';
      }
      cout << '\n';
    }
  }

  bool DFS(int start) {
    if (used_[start]) {
      return false;
    }
    used_[start] = true;
    for (int v : adjacency_list_[start]) {
      if (used_[a_size_ + v]) {
        continue;
      }
      used_[a_size_ + v] = true;
      if (matches_[v] == -1) {
        matches_[v] = start;
        return true;
      }
      if (DFS(matches_[v])) {
        matches_[v] = start;
        return true;
      }
    }
    return false;
  }

  int Kuhn() {
    matches_.resize(b_size_, -1);
    int matches_count = 0;
    for (int i = 0; i < a_size_; ++i) {
      used_.resize(a_size_ + b_size_, false);
      if (DFS(i)) {
        ++matches_count;
      }
    }
    return matches_count;
  }

  void DisplayMatches() {
    for (int v = 0; v < b_size_; ++v) {
      if (matches_[v] != -1) {
        cout << v + 1 << ' ' << matches_[v] + 1 << '\n';
      }
    }
  }

 private:
  vector<vector<int>> adjacency_list_;
  vector<bool> used_;
  vector<int> matches_;
  int a_size_ = 0;
  int b_size_ = 0;
};

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  Graph g(n, m);

  for (int i = 0; i < n; ++i) {
    int input = 0;
    while (true) {
      cin >> input;
      if (input == 0) {
        break;
      }
      g.AddEdge(i + 1, input);
    }
  }

  cout << g.Kuhn() << '\n';
  g.DisplayMatches();

  return 0;
}
