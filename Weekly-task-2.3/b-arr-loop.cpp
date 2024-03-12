#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

template <typename T>
bool IsInVector(vector<T> &the_vector, T searched) {
  uint32_t size = the_vector.size();
  for (uint32_t i = 0; i < size; ++i) {
    if (the_vector[i] == searched) {
      return true;
    }
  }
  return false;
}

void CleanLoop(uint32_t *loop, uint32_t meeting_point, uint32_t loop_size, uint32_t &loop_start) {
  for (uint32_t i = 0; i < loop_size; ++i) {
    if (loop[i] - 1 == meeting_point) {
      loop_start = i;
      break;
    }
    loop[i] = 0;
  }
}

bool LoopSearch(vector<uint32_t> *&edges, uint32_t start, uint16_t *&states, uint32_t *loop, uint32_t &loop_size,
                uint32_t vertexes_amount, uint32_t &loop_start) {
  states[start] = 1;
  loop[loop_size] = start + 1;
  loop_size++;
  vector<uint32_t> &children = edges[start];
  bool loop_exists = false;

  for (uint32_t i = 0; i < children.size(); ++i) {
    if (states[children[i]] == 0) {
      loop_exists = LoopSearch(edges, children[i], states, loop, loop_size, vertexes_amount, loop_start);
    } else if (states[children[i]] == 1) {
      loop_exists = true;
      CleanLoop(loop, children[i], loop_size, loop_start);
    }
    if (loop_exists) {
      break;
    }
  }

  if (!loop_exists) {
    loop[loop_size] = 0;
    loop_size--;
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
    if (!IsInVector(edges[from - 1], to - 1)) {
      edges[from - 1].push_back(to - 1);
    }
  }

  auto *loop = new uint32_t[vertexes_amount]{0};
  uint32_t loop_size = 0;
  uint32_t loop_start = 0;
  bool loop_exists = false;
  for (uint32_t i = 0; i < vertexes_amount; ++i) {
    if (states[i] == 0) {
      loop_exists = LoopSearch(edges, i, states, loop, loop_size, vertexes_amount, loop_start);
      if (loop_exists) {
        break;
      }
    }
  }

  if (loop_exists) {
    cout << "YES"
         << "\n";
    for (uint32_t i = loop_start; i < loop_size; ++i) {
      cout << loop[i] << " ";
    }
  } else {
    cout << "NO"
         << "\n";
  }

  delete[] edges;
  delete[] states;
  delete[] loop;
  return 0;
}
