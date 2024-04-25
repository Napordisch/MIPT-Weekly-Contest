#include <vector>
#include <iostream>
using std::cin;
using std::cout;
using std::vector;

class Graph { // 0-indexed inside of the class, 1-indexed outside of the class
 public:
  Graph(int amount_of_vertexes, int amount_of_edges) {
    amount_of_vertexes_ = amount_of_vertexes;
    amount_of_edges_ = amount_of_edges;
    list_.resize(amount_of_vertexes_);
    visited_.resize(amount_of_vertexes_, false);
  }

  void AddEdge(int from, int to) {
    list_[from - 1].push_back(to - 1);
  }

  void DisplayList() {
    for (int i = 0; i < amount_of_vertexes_; ++i) {
      cout << "from";
      cout << i + 1 << ':' << ' ';
      for (unsigned int j = 0; j < list_[i].size(); ++j) {
        cout << list_[i][j] << ' ';
      }
      cout << '\n';
    }
  }
  bool ExternalDFSCall(int start, int destination) {
    return DFS_(start - 1, destination - 1);
  }

  void FordFulkerson() {
    vector<int> flows(amount_of_vertexes_, 0);
    vector<int> parents(amount_of_vertexes_, -1);
    while (DFS
  }

 private:
  int source_ = 0;
  int target_ = 0;
  vector<vector<int>> list_;
  int amount_of_vertexes_ = 0;
  int amount_of_edges_ = 0;
  vector<bool> visited_;

  bool DFS_(int start, int destination) {
    cout << start + 1 << ' ';
    visited_[start] = true;
    if (start == destination) {
      return true;
    }
    for (int neighbour : list_[start]) {
      if (!visited_[neighbour]) {
        if (DFS_(neighbour, destination)) {
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
  Graph g(lawns_amount, roads_amount);
  for (int i = 0; i < roads_amount; ++i) {
    int from = 0; 
    int to = 0; 
    cin >> from >> to;
    g.AddEdge(from, to); // 1-indexed outside of the class, 0-indexed inside of the class
  }
  g.DisplayList();
  cout << "DFS:\n";
  g.ExternalDFSCall(1, 3);

  return 0;
}
