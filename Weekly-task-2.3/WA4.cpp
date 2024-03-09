#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

bool DepthFirstSearch(vector<uint32_t> *proximity_list, uint32_t vertexes_amount, uint16_t *states, uint32_t start,
                      vector<uint32_t> &loop, bool loop_exists) {
  states[start] = 1;
  const vector<uint32_t> &children = proximity_list[start];
  loop.push_back(start);

  for (uint32_t i = 0; i < children.size(); ++i) {
    if (states[children[i]] == 0 || states[children[i]] == 2) {
      loop_exists = DepthFirstSearch(proximity_list, vertexes_amount, states, children[i], loop, loop_exists);

      if (loop_exists) {
        return true;
      }
    }
    if (states[children[i]] == 1) {
      return true;
    }
    if (states[children[i]] == 2) {
      loop.pop_back();
      return false;
    }
  }
  states[start] = 2;
  loop.pop_back();
  return false;
}

int main() {
  uint32_t vertexes_amount = 0;
  uint32_t edges_amount = 0;
  cin >> vertexes_amount >> edges_amount;
  auto *states = new uint16_t[vertexes_amount]{0};  // 0 - white, 1 - grey, 2 - black
  auto *proximity_list = new vector<uint32_t>[vertexes_amount];

  for (uint32_t i = 0; i < edges_amount; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    if (from != 0 && to != 0) {
    proximity_list[from - 1].push_back(to - 1);
    }
  }

  //  list display
  //	for (uint32_t i = 0; i < vertexes_amount; ++i) {
  //		for (uint32_t j = 0; j < proximity_list[i].size(); ++j) {
  //			cout << proximity_list[i][j] << " ";
  //		}
  //		cout << "\n";
  //	}

  vector<uint32_t> loop;
  bool loop_exists = false;
  for (uint32_t i = 0; i < vertexes_amount; ++i) {
    if (states[i] == 0) {
      if (DepthFirstSearch(proximity_list, vertexes_amount, states, i, loop, loop_exists)) {
        loop_exists = true;
        break;
      }
    }
  }
  if (loop_exists) {
    cout << "YES"
         << "\n";
    for (uint32_t i = 0; i < loop.size(); ++i) {
      cout << loop[i] + 1 << " ";
    }
  } else if (!loop_exists) {
    cout << "NO"
         << "\n";
  }

  delete[] proximity_list;
  delete[] states;
  return 0;
}

