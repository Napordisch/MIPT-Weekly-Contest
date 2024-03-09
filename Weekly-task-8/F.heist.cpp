#include <iostream>

struct Item {
  uint32_t cost;
  uint32_t weight;
};

int main() {
  uint32_t w, n;
  std::cin >> w >> n;
  auto* flat = new Item[n];
  for (uint32_t i = 0; i < n; i++) {
    std::cin >> flat[i].cost >> flat[i].weight;
  }

  auto** table = new uint32_t*[w + 1];
  for (uint32_t i = 0; i < w + 1; i++) {
    table[i] = new uint32_t[n + 1];
    for (uint32_t j = 0; j < n + 1; j++) {
      table[i][j] = 0;
    }
  }
  uint32_t amount = 0;
  for (uint32_t j = 1; j <= w; j++) {
    for (uint32_t i = 1; i <= n; i++) {
      table[j][i] = table[j][i - 1];
      if (flat[i - 1].weight <= j) {
        uint32_t t = table[j - flat[i - 1].weight][i - 1] + flat[i - 1].cost;
        if (t > table[j][i]) {
          table[j][i] = t;
          amount = i;
        }
      }
    }
  }
  uint32_t max_cost = 0;
  uint32_t min_weight = w;
  for (uint32_t j = 1; j <= w; j++) {
    if (table[j][amount] > max_cost) {
      max_cost = table[j][amount];
      min_weight = j;
    }
  }

  std::cout << max_cost << " " << min_weight;
  for (uint32_t i = 0; i < w + 1; i++) {
    delete[] table[i];
  }
  delete[] flat;
  delete[] table;
  return 0;
}