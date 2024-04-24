#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::min;
using std::priority_queue;
using std::vector;

template <typename T>
void Display2DVector(vector<vector<T>> the_vector) {
  for (int i = 0; i < the_vector.size(); ++i) {
    cout << "From" << i + 1 << ':' << ' ';
    for (int vertex : the_vector[i]) {
      cout << vertex + 1 << ' ';
    }
    cout << '\n';
  }
}

void DFS(const vector<vector<int>> &graph, const int &start, vector<bool> &used,
         priority_queue<int, vector<int>, std::greater<int>> &points, vector<int> &depths, vector<int> &back_depths,
         int parent = -1) {
  used[start] = true;

  if (parent == -1) {
    back_depths[start] = 0;
  } else {
    back_depths[start] = back_depths[parent] + 1;
  }
  depths[start] = back_depths[start];

  int neighbours = 0;
  for (int u : graph[start]) {
    if (u == parent) {
      continue;
    }
    if (used[u]) {
      depths[start] = min(depths[start], back_depths[u]);
    } else {
      DFS(graph, u, used, points, depths, back_depths, start);
      depths[start] = min(depths[start], depths[u]);
      if (back_depths[start] <= depths[u] && parent != -1) {
        points.push(start);
      }
      neighbours++;
    }
  }
  if (parent == -1 && neighbours > 1) {
    points.push(start);
  }
}

void AnswerOutput(priority_queue<int, vector<int>, std::greater<int>> &points) {
  std::queue<int> answer;
  int last_elem = 0;
  while (!points.empty()) {
    if (points.top() + 1 != last_elem) {
      answer.push(points.top() + 1);
    }
    last_elem = points.top() + 1;
    points.pop();
  }

  cout << answer.size() << '\n';
  while (!answer.empty()) {
    cout << answer.front() << '\n';
    answer.pop();
  }
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<vector<int>> graph(n);
  vector<bool> used(n);
  vector<int> depths(n);
  vector<int> back_depths(n);

  priority_queue<int, vector<int>, std::greater<int>> points;

  for (int i = 0; i < m; ++i) {
    int a = 0;
    int b = 0;
    cin >> a >> b;
    if (a == b) {
      continue;
    }
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFS(graph, i, used, points, depths, back_depths);
    }
  }

  AnswerOutput(points);
}
