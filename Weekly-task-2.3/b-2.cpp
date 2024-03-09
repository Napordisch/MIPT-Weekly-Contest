#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
  uint32_t vertexes_amount = 0;
  uint32_t edges_amount = 0;
  cin >> vertexes_amount >> edges_amount;

  vector<uint32_t> *proximity_list = new vector<uint32_t>[vertexes_amount];
  for (uint32_t i = 0; i < edges_amount; ++i) {
    uint32_t from;
    uint32_t to;
    cin >> from >> to;
    proximity_list[from - 1].push_back(to - 1);
  }

  return 0;
}
