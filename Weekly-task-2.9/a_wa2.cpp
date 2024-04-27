#include <limits>
#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class Graph {
 public:
  Graph(int vertexes_amount, int edges_amount, int start, int end) {
    vertexes_amount_ = vertexes_amount;
    edges_amount_ = edges_amount;
    source_ = start - 1;
    target_ = end - 1;
    capacities_.resize(vertexes_amount_, vector<int>(vertexes_amount_, 0));
  }

  void AddEdge(int from, int to) {
    capacities_[from - 1][to - 1] = 1;
  }

  void DisplayGraph() {
    for (int i = 0; i < vertexes_amount_; ++i) {
      cout << "from " << i + 1 << ':' << ' ';
      for (int j = 0; j < vertexes_amount_; ++j) {
        if (capacities_[i][j] >= 1) {
          cout << j + 1 << ' ';
        }
      }
      cout << '\n';
    }
  }

  void DisplayGraphTable() {
    for (int i = 0; i < vertexes_amount_; ++i) {
      for (int j = 0; j < vertexes_amount_; ++j) {
        cout << capacities_[i][j] << ' ';
      }
      cout << '\n';
    }
  }

  int FordFulkerson() {
    int flow = 0;
    vector<int> parents(vertexes_amount_, -1);
    visited_.resize(vertexes_amount_, false);
    while (DFS(source_, target_, parents, visited_)) {
      std::stack<int> current_path;
      int current_path_flow = std::numeric_limits<int>::max();

      for (int i = target_; i != source_; i = parents[i]) {
        if (current_path_flow > capacities_[parents[i]][i]) {
          current_path_flow = capacities_[parents[i]][i];
        }
        current_path.push(i);
      }

      current_path.push(source_);  // because we don't touch the source vertex
                                   // when going through the path in cycles

      for (int i = target_; i != source_; i = parents[i]) {
        capacities_[parents[i]][i] -= current_path_flow;
        capacities_[i][parents[i]] += current_path_flow;
      }

      flow += current_path_flow;
      paths_.push_back(current_path);

      for (unsigned int i = 0; i < visited_.size(); ++i) {
        visited_[i] = false;
      }
    }

    return flow;
  }

  void DisplayPaths() {
    for (int i = 0; i < 2; ++i) {
      while (!paths_[i].empty()) {
        cout << paths_[i].top() + 1 << ' ';
        paths_[i].pop();
      }
      cout << '\n';
    }
  }

  bool DFS(int start, int destination, vector<int> &parents, vector<bool> &visited) {
    visited[start] = true;
    if (start == destination) {
      return true;
    }
    for (int neighbour = 0; neighbour < vertexes_amount_; ++neighbour) {
      if (capacities_[start][neighbour] > 0 && !visited[neighbour]) {
        if (DFS(neighbour, destination, parents, visited)) {
          parents[neighbour] = start;
          return true;
        }
      }
    }
    return false;
  }

 private:
  int vertexes_amount_ = 0;
  int edges_amount_ = 0;
  int source_ = 0;
  int target_ = 0;
  vector<std::stack<int>> paths_;

  vector<vector<int>> capacities_;
  vector<bool> visited_;
};

int main() {
  int lawns_amount = 0;  // n
  int roads_amount = 0;  // m
  int apricot_lawn = 0;  // s
  int home_lawn = 0;     // t
  cin >> lawns_amount >> roads_amount >> apricot_lawn >> home_lawn;
  Graph g(lawns_amount, roads_amount, apricot_lawn, home_lawn);
  for (int i = 0; i < roads_amount; ++i) {
    int from = 0;
    int to = 0;
    cin >> from >> to;
    g.AddEdge(from,
              to);  // 1-indexed outside of the class, 0-indexed inside of the class
  }

  if (g.FordFulkerson() >= 0) {
    cout << "YES\n";
    g.DisplayPaths();
  } else {
    cout << "NO";
  }

  return 0;
}
