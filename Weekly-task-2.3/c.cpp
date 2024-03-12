#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void DFS(vector<int> *adjacency, int start, int n, vector<int> &subnet,
         unsigned int *states) {
  states[start] = 1;
  subnet.push_back(start);
  vector<int> &children = adjacency[start];
  unsigned int size = children.size();
  for (unsigned i = 0; i < size; ++i) {
    if (states[children[i]] == 0) {
      DFS(adjacency, children[i], n, subnet, states);
    }
  }
  states[start] = 2;
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<int> *adjacency = new vector<int>[n];
  unsigned int *states = new unsigned int[n]{};
  for (unsigned int l = 0; l < m; ++l) {
    int i = 0;
    int j = 0;
    cin >> i >> j;
    adjacency[i - 1].push_back(j - 1);
  }
  vector<vector<int>> connections;
  for (unsigned int i = 0; i < n; ++i) {
    DFS(adjacency, i, n, connections, unsigned int *states)
  }
}
