#include <vector>
#include <iostream>
#include <climits>

using std::cin;
using std::cout;
using std::vector;

class Graph { // 0-indexed inside of the class, 1-indexed outside of the class
 public:
  Graph(int amount_of_vertexes, int amount_of_edges, int source, int destination) {
    amount_of_vertexes_ = amount_of_vertexes;
    amount_of_edges_ = amount_of_edges;
    list_.resize(amount_of_vertexes_);
    visited_.resize(amount_of_vertexes_, false);
    source_ = source - 1;
    target_ = destination - 1;
  }

  void AddEdge(int from, int to) {
    list_[from - 1].push_back(to - 1);
  }

  void DisplayList() {
    for (int i = 0; i < amount_of_vertexes_; ++i) {
      cout << "from";
      cout << i + 1 << ':' << ' ';
      for (unsigned int j = 0; j < list_[i].size(); ++j) {
        cout << list_[i][j] + 1 << ' ';
      }
      cout << '\n';
    }
  }

  void FordFulkerson() {
    int amount_of_flows = 0;
    vector<vector<int>> flows(amount_of_vertexes_,
                        vector<int>(amount_of_vertexes_, 0));
    vector<int> parents(amount_of_vertexes_, -1);
    vector<vector<int>> capacity(amount_of_vertexes_, vector<int>(amount_of_vertexes_, 1));
    while (DFS_(source_, target_, parents)) {
      int residual_path_capacity = INT_MAX;
      int i = target_;
      for (int i = target_; i != source_; i = parents[i]) {
        if (residual_path_capacity > capacity[parents[i]][i]) {
          residual_path_capacity = capacity[parents[i]][i];
        }
      }
      for (int i = target_; i != source_; i = parents[i]) {
        flows[parents[i]][i] = flows[parents[i]][i] + residual_path_capacity;
        flows[i][parents[i]] = -flows[parents[i]][i];
      }
    }

    for (int i = 0; i < amount_of_vertexes_; ++i) {
      amount_of_flows += flows[i][target_];
    }

    cout << amount_of_flows << '\n';

  }

 private:
  int source_ = 0;
  int target_ = 0;
  vector<vector<int>> list_;
  int amount_of_vertexes_ = 0;
  int amount_of_edges_ = 0;
  vector<bool> visited_;

  bool DFS_(int start, int destination, vector<int> &parents) {
    cout << start + 1 << ' ';
    visited_[start] = true;
    if (start == destination) {
      return true;
    }
    for (int neighbour : list_[start]) {
      if (!visited_[neighbour]) {
        if (DFS_(neighbour, destination, parents)) {
          parents[neighbour] = start;
          return true;
        }
      }
    }
    return false;
  }
};

int main() {
  int lawns_amount = 0; // n
  int roads_amount = 0; // m
  int apricot_lawn = 0; // s
  int home_lawn = 0; // t
  cin >> lawns_amount >> roads_amount >> apricot_lawn >> home_lawn;
  Graph g(lawns_amount, roads_amount, apricot_lawn, home_lawn);
  for (int i = 0; i < roads_amount; ++i) {
    int from = 0; 
    int to = 0; 
    cin >> from >> to;
    g.AddEdge(from, to); // 1-indexed outside of the class, 0-indexed inside of the class
  }
  g.DisplayList();
  g.FordFulkerson();

  return 0;
}
