#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

using UINT = uint32_t;

void ReverseVector(vector<UINT> &main_vector) {
  UINT size = main_vector.size();
  vector<UINT> old_vector = main_vector;
  for (UINT i = 0; i < size; ++i) {
    main_vector[i] = old_vector[size - i - 1];
  }
}

void ShowVertexesVector(const vector<UINT> &the_vector) {
  UINT size = the_vector.size();
  for (UINT i = 0; i < size; ++i) {
    cout << the_vector[i] + 1 << " ";
  }
  cout << "\n";
}

class Graph {
 public:
  Graph(UINT n, UINT m) {
    amount_of_edges_ = n;
    amount_of_vertexes_ = m;
    proximity_ = new vector<UINT>[amount_of_vertexes_];
    states_ = new uint16_t[amount_of_vertexes_]{0};
  }

  void Fill() {
    for (UINT i = 0; i < amount_of_vertexes_; ++i) {
      UINT from = 0;
      UINT to = 0;
      cin >> from >> to;
      if (from != 0 && to != 0) {
        proximity_[from - 1].push_back(to - 1);
      }
    }
  }

  void Display() {
    cout << "Adjacency list:"
         << "\n";
    for (UINT i = 0; i < amount_of_vertexes_; ++i) {
      vector<UINT> &children = proximity_[i];
      cout << "[" << i + 1 << "]: ";
      ShowVertexesVector(children);
    }
  }

  bool DFS(UINT start) {
    states_[start] = 1;
    vector<UINT> &children = proximity_[start];
    UINT size = children.size();
    bool cycle = false;
    for (UINT i = 0; i < size; ++i) {
      if (states_[children[i]] == 1) {
        return true;
      }
      if (states_[children[i]] == 0) {
        cycle = DFS(children[i]);
      }
      if (cycle) {
        return true;
      }
    }
    states_[start] = 2;
    top_sort_.push_back(start);
    return cycle;
  }

  bool TopologicalSort() {
    for (UINT i = 0; i < amount_of_vertexes_; ++i) {
      if (states_[i] == 0) {
        bool cycle = DFS(i);
        if (cycle) {
          return false;
        }
      }
    }
    ReverseVector(top_sort_);
    ShowVertexesVector(top_sort_);
    return true;
  }

  ~Graph() {
    delete[] states_;
    delete[] proximity_;
  }

 private:
  vector<UINT> top_sort_;
  UINT amount_of_vertexes_ = 0;
  UINT amount_of_edges_ = 0;
  uint16_t *states_ = nullptr;  // 0 - not visited, 1 - visited, 2 - came back through
  vector<UINT> *proximity_ = nullptr;
};

int main() {
  UINT n = 0;
  UINT m = 0;
  cin >> n >> m;
  if (m == 0 || n == 0) {
    cout << -1 << "\n";
    return 0;
  }
  Graph the_graph(n, m);
  the_graph.Fill();
  bool top_sort_possible = the_graph.TopologicalSort();
  if (!top_sort_possible) {
    cout << -1 << "\n";
  }
  return 0;
}