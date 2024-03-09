#include <cstdint>
#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;

using std::list;

void CleanLoop(list<uint32_t> &loop, uint32_t meeting_point) {
  while (loop.front() != meeting_point && !loop.empty()) {
    loop.pop_front();
  }
}

bool LoopSearch(std::vector<uint32_t> *edges, uint32_t start, uint16_t *&states,
                list<uint32_t> &loop) {
  list<uint32_t> dfs_stack;
  dfs_stack.push_front(start);
  bool loop_exists = false;

  while (true) {
    runner = dfs_stack.front();
    loop.push_back(runner);
    state[runner] = 1;
    loop.push_back(runner);
    dfs_stack.push_front(runner);
    std::vector<uint32_t> &children = edges[runner];
    uint32_t amount_of_children = children.size();

    // choosing where to go and detecting loop
    for (uint32_t i = 0; i < amount_of_children; ++i) {
      if (states[children[i]] == 1) {
        loop_exists = true;
        break;
      }
      if (states[children[i]] == 0) {
        dfs_stack.push_front(children[i]);
      }
    }
  }

  for (uint32_t i = 0; i < children.size(); ++i) {
    if (states[children[i]] == 0) {
      loop_exists = LoopSearch(edges, vertexes_amount, children[i], states, loop);
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

  auto *edges = new std::vector<uint32_t>[vertexes_amount];
  auto *states = new uint16_t[vertexes_amount]{0};

  for (uint32_t i = 0; i < edges_amount; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    if (from != 0 && to != 0) {
      edges[from - 1].push_back(to - 1);
    }
  }

  list<uint32_t> loop;
  bool loop_exists = false;
  for (uint32_t i = 0; i < vertexes_amount; ++i) {
    if (states[i] == 0) {
      loop_exists = LoopSearch(edges, vertexes_amount, i, states, loop);
      if (loop_exists) {
        break;
      }
    }
  }

  if (loop_exists) {
    cout << "YES"
         << "\n";
    while (!loop.empty()) {
      cout << loop.front() + 1 << " ";
      loop.pop_front();
    }
  } else {
    cout << "NO"
         << "\n";
  }

  delete[] edges;
  delete[] states;
  return 0;
}
