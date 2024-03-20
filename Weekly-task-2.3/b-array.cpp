#include <cstdint>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class PushPopArray {
public:
  PushPopArray(uint32_t size) {
    if (size_ == 0) {
      return;
    }
    size_ = size;
    array_ = new uint32_t[size];
  }

  ~PushPopArray() {
    delete[] array_;
  }

  void push_back(uint32_t value) {
    array_[index_] = value;
    index_++;
  }

  uint32_t pop_back() {
    index_--;
    return array_[index_ + 1];
  }

  void pop_front() {
    start_++;
    size_--;
  }

  uint32_t operator[](uint32_t index) {
    return array_[index + start_];
  }

  void Reset() {
    index_ = 0;
    start_ = 0;
  }

  uint32_t size() {
    return index_ - start_;
  }

private:
  uint32_t index_ = 0;
  uint32_t *array_ = nullptr;
  uint32_t size_ = 0;
  uint32_t start_ = 0;
};


void CleanLoop(PushPopArray &loop, uint32_t meeting_point) {
  while (loop[0] != meeting_point) {
    loop.pop_front();
  }
}

bool LoopSearch(PushPopArray *edges, uint32_t vertexes_amount, uint32_t start, uint16_t *&states,
                PushPopArray &loop) {
  states[start] = 1;
  loop.push_back(start);
  PushPopArray &children = edges[start];
  bool loop_exists = false;

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

  auto edges = new PushPopArray *[vertexes_amount];
  // for (uint32_t i = 0; i < vertexes_amount; ++i) {
  //   edges[i] = new PushPopArray(vertexes_amount);
  // }

  auto *states = new uint16_t[vertexes_amount]{0};

  for (uint32_t i = 0; i < edges_amount; ++i) {
    uint32_t from = 0;
    uint32_t to = 0;
    cin >> from >> to;
    if (from != 0 && to != 0) {
      edges[from - 1].push_back(to - 1);
    }
  }

  PushPopArray loop(vertexes_amount);
  bool loop_exists = false;
  for (uint32_t i = 0; i < vertexes_amount; ++i) {
    if (states[i] == 0) {
      loop_exists = LoopSearch(edges, vertexes_amount, i, states, loop);
      if (loop_exists) {
        break;
      }
      loop.Reset();
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
