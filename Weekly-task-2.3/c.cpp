#include <iostream>

using std::cin;
using std::cout;

void DepthFirstSearch(std::vector<uint32_t> *&edges, uint32_t start,
                      uint16_t *&states, vector<uint32_t> &group) {
  states[start] = 1;
  const std::vector<uint32_t> &children = edges[start];

  for (uint32_t i = 0; i < children.size(); ++i) {
    if (states[children[i]] == 0) {
      DepthFirstSearch(edges, children[i], states, group);
    }
  }
  states[start] = 2;
}

int main() {
  uint32_t vertexes_amount = 0;
  uint32_t edges_amount = 0;
  cin >> vertexes_amount;
  cin >> edges_amount;

  auto *edges = new std::vector<uint32_t>[vertexes_amount];
  auto *states = new uint16_t[vertexes_amount]{0};

  for (uint32_t i = 0; i < edges_amount; ++i) {
    uint32_t student_a = 0;
    uint32_t student_b = 0;
    cin >> from >> to;
    if (from != 0 && to != 0) {
      edges[student_a - 1].push_back(student_b - 1);
      edges[student_b - 1].push_back(student_a - 1);
    }
  }
  vector<vector<uint32_t>> groups;
  for (uint32_t i = 0; i < vertexes_amount; ++i) {
    if (states[i] == 0) {
      groups.push_back();
      DepthFirstSearch(edges, i, states, groups.back());
    }
    return 0
  }
