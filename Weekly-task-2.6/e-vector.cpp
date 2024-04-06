#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::min;
using std::vector;

struct Edge {
  Edge() = default;
  Edge(int id, int t) {
    index = id;
    to = t;
  }
  int index = 0;
  int to = 0;
};

void DisplayVector(vector<int> the_vector) {
  for (int i = 0; i < static_cast<int>(the_vector.size()); ++i) {
    cout << the_vector[i] << ' ';
  }
  cout << '\n';
}

void DFS(const vector<vector<Edge> > &graph_list, int start, vector<bool> &used, vector<int> &depths,
         vector<int> &cycle_depths, vector<int> &bridges, int parent) {
  used[start] = true;

  if (parent == -1) {
    cycle_depths[start] = 0;
    depths[start] = cycle_depths[start];
  } else {
    cycle_depths[start] = cycle_depths[parent] + 1;
    depths[start] = cycle_depths[start];
  }
  const vector<Edge> &neighbours = graph_list[start];
  int amount_of_neighbours = static_cast<int>(neighbours.size());

  for (int i = 0; i < amount_of_neighbours; ++i) {
    const Edge &u_edge = neighbours[i];
    int u = u_edge.to;

    if (u == parent) {
      continue;
    }

    if (used[u]) {  // reverse edge
      depths[start] = min(depths[start], cycle_depths[u]);
    } else {  // straight edge
      DFS(graph_list, u, used, depths, cycle_depths, bridges, start);
      depths[start] = min(depths[start], depths[u]);
      if (cycle_depths[start] < depths[u]) {
        bridges.push_back(u_edge.index);
      }
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<vector<Edge> > graph_list(n);
  vector<bool> used(n, false);
  vector<int> depths(n);
  vector<int> cycle_depths(n);
  vector<int> bridges;
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    cin >> from >> to;
    graph_list[from - 1].emplace_back(i + 1, to - 1);
    graph_list[to - 1].emplace_back(i + 1, from - 1);
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFS(graph_list, i, used, depths, cycle_depths, bridges, -1);
    }
  }
  std::sort(bridges.begin(), bridges.end());
  cout << bridges.size() << '\n';
  DisplayVector(bridges);
}
