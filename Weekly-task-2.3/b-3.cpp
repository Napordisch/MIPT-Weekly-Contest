#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void CleanLoop(vector<uint32_t> &loop, uint32_t meeting_point) {
  while (loop[0] != meeting_point) {
    loop.erase(loop.begin());
  }
}

bool LoopSearch(vector<uint32_t> *edges, uint32_t start, uint16_t *&states,
                vector<uint32_t> &loop) {
  states[start] = 1;
  loop.push_back(start);
  vector<uint32_t> children = edges[start];
  bool loop_exists = false;

  for (uint32_t i = 0; i < children.size(); ++i) {
    if (states[children[i]] == 0) {
      loop_exists = LoopSearch(edges, children[i], states, loop);
    } else if (states[children[i]] == 1) {
      loop_exists = true;
      CleanLoop(loop, children[i]);
    }
    if (loop_exists) {
      break;
    }
  }

  if (!loop_exists) {
    loop.pop_back();
  }

  states[start] = 2;
  return loop_exists;
}

int main() {
  uint32_t vertexes_amount = 0;
  uint32_t edges_amount = 0;
  cin >> vertexes_amount;
  cin >> edges_amount;

  if (edges_amount == 0) {
    cout << "NO"
         << "\n";
    return 0;
  }

  auto *edges = new vector<uint32_t>[vertexes_amount];
  auto *states = new uint16_t[vertexes_amount]{0};

  for (uint32_t i = 0; i < edges_amount; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    if (from != 0 && to != 0) {
      edges[from - 1].push_back(to - 1);
    }
  }

  vector<uint32_t> loop;
  bool loop_exists = false;
  for (uint32_t i = 0; i < vertexes_amount; ++i) {
    if (states[i] == 0) {
      loop_exists = LoopSearch(edges, i, states, loop);
      if (loop_exists) {
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
  } else {
    cout << "NO"
         << "\n";
  }

  delete[] edges;
  delete[] states;
  return 0;
}
