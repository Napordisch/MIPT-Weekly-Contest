#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::min;
using std::priority_queue;
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

void DFS(const vector<vector<Edge>> &graph_list, int start, vector<bool> &used, vector<int> &depths,
         vector<int> &cycle_depths, priority_queue<int, vector<int>, std::greater<int>> &bridges, int parent) {
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
        bridges.push(u_edge.index);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<vector<Edge>> graph_list(n);
  vector<bool> used(n, false);
  vector<int> depths(n);
  vector<int> cycle_depths(n);
  priority_queue<int, vector<int>, std::greater<int>> bridges;
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    cin >> from >> to;
    if (from == to) {
      continue;
    }

    // checking for parallel edges
    // bool met = false;
    // for (int i = 0; i < static_cast<int>(graph_list[from - 1].size()); ++i) {
    //   if ((to - 1) == graph_list[from - 1][i].to) {
    //     met = true;
    //   }
    // }
    // if (met) {
    //   continue;
    // }

    graph_list[from - 1].emplace_back(i + 1, to - 1);
    graph_list[to - 1].emplace_back(i + 1, from - 1);
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFS(graph_list, i, used, depths, cycle_depths, bridges, -1);
    }
  }
  cout << bridges.size() << '\n';
  while (!bridges.empty()) {
    cout << bridges.top() << ' ';
    bridges.pop();
  }
}
