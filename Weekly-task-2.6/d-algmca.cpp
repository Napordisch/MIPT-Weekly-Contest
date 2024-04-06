#include <iostream>
#include <vector>
#include <queue>

using std::min;
using std::priority_queue;
using std::vector;

using std::cin;
using std::cout;

struct Edge {
  Edge() = default;
  Edge(int id, int t) {
    index = id;
    to = t;
  }
  int index = 0;
  int to = 0;
};

void DFS(int start, vector<vector<Edge>> &graph, vector<bool> &used, vector<int> &depths, vector<int> &back_depths,
         priority_queue<int, vector<int>, std::greater<int>> &points, int p = -1) {
  used[start] = true;
  depths[start] = back_depths[start] = (p == -1 ? 0 : back_depths[p] + 1);
  int neighbours = 0;
  for (Edge u : graph[start]) {
    if (u.to != p) {
      if (used[u.to]) {
        depths[start] = min(depths[start], back_depths[u.to]);
      } else {
        DFS(u.to, graph, used, depths, back_depths, points, start);
        depths[start] = min(depths[start], depths[u.to]);
        if (back_depths[start] <= depths[u.to] && p != -1) {
          points.push(start);
        }
        neighbours++;
      }
    }
  }
  if (p == -1 && neighbours > 1) {
    points.push(start);
  }
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<vector<Edge>> graph_list(n);
  vector<bool> used(n, false);
  vector<int> depths(n);
  vector<int> back_depths(n);
  priority_queue<int, vector<int>, std::greater<int>> points;

  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    cin >> from >> to;
    if (from == to) {
      continue;
    }
    // checking for parallel edges
    bool met = false;
    for (int i = 0; i < static_cast<int>(graph_list[from - 1].size()); ++i) {
      if ((to - 1) == graph_list[from - 1][i].to) {
        met = true;
      }
    }
    if (met) {
      continue;
    }
    graph_list[from - 1].emplace_back(i + 1, to - 1);
    graph_list[to - 1].emplace_back(i + 1, from - 1);
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFS(i, graph_list, used, depths, back_depths, points);
    }
  }

  cout << points.size() << '\n';
  while (!points.empty()) {
    cout << points.top() + 1 << '\n';
    points.pop();
  }
}