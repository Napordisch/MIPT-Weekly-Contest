#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

bool DFS(vector<uint32_t> *proximity, uint16_t *states, uint32_t start, vector<uint32_t> &top_sort) {
  states[start] = 1;
  vector<uint32_t> &children = proximity[start];
  uint32_t amount_of_children = children.size();
  bool cycle = false;

  for (uint32_t i = 0; i < amount_of_children; ++i) {
    if (states[children[i]] == 0) {
      cycle = DFS(proximity, states, children[i], top_sort);
    } else if ((states[children[i]]) == 1) {
      cycle = true;
    }
    if (cycle) {
      break;
    }
  }

  top_sort.push_back(start);
  states[start] = 2;
  return cycle;
}

int main() {
  uint32_t n = 0;
  uint32_t m = 0;
  cin >> n >> m;
  auto *proximity = new vector<uint32_t>[n];
  auto *states = new uint16_t[n]{};  // 0 - not visited, 1 - innned, 2 - outed

  for (uint32_t i = 0; i < m; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    proximity[from - 1].push_back(to - 1);
  }

  bool cycle = false;

  vector<uint32_t> top_sort;

  for (uint32_t i = 0; i < n; ++i) {
    if (states[i] == 0) {
      cycle = DFS(proximity, states, i, top_sort);
      if (cycle) {
        break;
      }
    }
  }

  if (cycle) {
    cout << "-1"
         << "\n";
  } else {
    uint32_t top_sort_size = top_sort.size();
    for (size_t i = 0; i < top_sort_size; ++i) {
      cout << top_sort[top_sort_size - 1 - i] + 1 << " ";
    }
  }

  delete[] proximity;
  return 0;
}