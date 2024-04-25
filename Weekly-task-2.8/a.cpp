#include <vector>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using std::priority_queue;
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
    vector<int> &neighbours = adjacency_list_[start];
    for (unsigned int i = 0; i < neighbours.size(); ++i) {

      if (used_[a_size_ + neighbours[i]]) {
        continue;
      }
      used_[a_size_ + neighbours[i]] = true;

      int to = neighbours[i];
      if (matches_[to] == -1) {
        matches_[to] = start;
        return true;
      }

      if (DFS(matches_[to])) {
        matches_[to] = start;
        return true;
      }
    }
    return false;
  }

  int Kuhn() {
    int matches_count = 0;
    matches_.resize(b_size_, -1);
    for (int v = 0; v < static_cast<int>(a_size_); ++v) {
      used_.resize(a_size_ + b_size_, false);
      if (DFS(v)) {
        ++matches_count;
      }
    }
    return matches_count;
  }

  void DisplayMatches() {

    for (unsigned int i = 0; i < b_size_; ++i) {
      if (matches_[i] != -1) {
        cout << matches_[i] + 1 << ' ' << i + 1 << '\n';
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