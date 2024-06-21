#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

template <typename T>
void DisplayTable(const vector<vector<T>> &table) {
  for (const vector<T> &row : table) {
    for (const T &cell : row) {
      cout << cell << '\t';
    }
    cout << '\n';
  }
}

class Graph {
 public:
  explicit Graph(int n) : size(n), capacity(n, vector<int>(n, 0)), flow(n, vector<int>(n, 0)) {
  }
  int size;
  vector<vector<int>> capacity;
  vector<vector<int>> flow;
  void AddEdge(int from, int to, int weight) {
    capacity[from - 1][to - 1] += weight;
  }
  void ShowBFS() {
    vector<int> parents(size, -1);
    Bfs(0, size - 1, parents);
  }
  int CalculateFlow(int from, int to) {
    from--;
    to--;
    vector<int> parents(size, -1);
    int max_flow = std::numeric_limits<int>::min();
    while (Bfs(from, to, parents)) {
      int residual_path_capacity = std::numeric_limits<int>::max();

      int current = to;
      int previous = parents[current];
      while (previous != -1) {
        int this_edge_residual_capacity = ResidualCapacity(previous, current);
        if (residual_path_capacity > this_edge_residual_capacity) {
          residual_path_capacity = this_edge_residual_capacity;
        }
        current = previous;
        previous = parents[current];
      }
      current = to;
      previous = parents[current];
      while (previous != -1) {
        AddFlow(previous, current, residual_path_capacity);
        if (max_flow < flow[previous][current]) {
          max_flow = flow[previous][current];
        }
        current = previous;
        previous = parents[current];
      }
    }
    return InFlow(to);
  }

 private:
  inline int ResidualCapacity(const int &from, const int &to) const {
    return capacity[from][to] - flow[from][to];
  }

  inline void AddFlow(const int &from, const int &to, const int &amount) {
    flow[from][to] += amount;
    flow[to][from] -= amount;
  }

  bool Bfs(const int &root, const int &goal, vector<int> &parents) {
    vector<bool> visited(size, false);
    visited[root] = true;
    queue<int> q;
    q.push(root);

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      for (int adjacent_vertex = 0; adjacent_vertex < size; ++adjacent_vertex) {
        if (!visited[adjacent_vertex] && ResidualCapacity(vertex, adjacent_vertex) > 0) {
          parents[adjacent_vertex] = vertex;
          visited[adjacent_vertex] = true;
          if (adjacent_vertex == goal) {
            return true;
          }
          q.push(adjacent_vertex);
        }
      }
    }
    return false;
  }

  int InFlow(int vertex) {
    int flow_sum = 0;
    for (int i = 0; i < size; ++i) {
      flow_sum += flow[i][vertex];
    }
    return flow_sum;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int weight = 0;
    cin >> from >> to >> weight;
    g.AddEdge(from, to, weight);
  }
  cout << g.CalculateFlow(1, n) << '\n';
}
