#include <iostream>
#include <vector>
#include <stack>

using std::cin;
using std::cout;

using std::stack;
using std::vector;

struct Graph {
  explicit Graph(int n) : state(n), adjacency_list(n), size(n) {
  }
  void AddEdge(int from, int to) {
    --from;
    --to;
    adjacency_list[from].push_back(to);
  }

  vector<int> state;
  stack<int> cycle;
  bool cycle_complete;
  vector<vector<int>> adjacency_list;
  int size;

  bool FindCycles() {
    for (int i = 0; i < size; ++i) {
      if (state[i] == 0) {
        if (FindCycle(i)) {
          return true;
        }
      }
    }
    return false;
  }

  bool FindCycle(int start) {
    state[start] = 1;
    bool cycle_exists = false;
    for (int vertex : adjacency_list[start]) {
      if (state[vertex] == 1) {
        cycle_exists = true;
        state[vertex] = 2;
      } else if (state[vertex] == 0) {
        cycle_exists = FindCycle(vertex);
      }
      if (cycle_exists) {
        break;
      }
    }

    if (!cycle_complete && cycle_exists) {
      cycle.push(start);
    }

    if (state[start] == 2) {
      cycle_complete = true;
    }
    state[start] = 2;
    return cycle_exists;
  }

  void PrintCycle() {
    while (!cycle.empty()) {
      cout << cycle.top() + 1 << ' ';
      cycle.pop();
    }
    cout << '\n';
  }
};

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    cin >> from >> to;
    g.AddEdge(from, to);
  }
  if (g.FindCycles()) {
    cout << "YES" << '\n';
    g.PrintCycle();
  } else {
    cout << "NO" << '\n';
  }
}
