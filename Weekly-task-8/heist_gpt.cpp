#include <iostream>

struct Item {
  uint32_t cost;
  uint32_t weight;
};

int main() {
  uint32_t w, n;
  std::cin >> w >> n;
  auto* flat = new Item[n + 1];
  for (uint32_t i = 1; i <= n; i++) {
    std::cin >> flat[i].cost >> flat[i].weight;
  }

  auto** table = new uint32_t*[w + 1];
  for (uint32_t i = 0; i <= w; i++) {
    table[i] = new uint32_t[n + 1];
    for (uint32_t j = 0; j <= n; j++) {
      table[i][j] = 0;
    }
  }

  uint32_t amount = 0;
  for (uint32_t i = 1; i <= n; i++) {
    for (uint32_t j = 1; j <= w; j++) {
      table[j][i] = table[j][i - 1];
      if (flat[i].weight <= j) {
        uint32_t t = table[j - flat[i].weight][i - 1] + flat[i].cost;
        if (t > table[j][i]) {
          table[j][i] = t;
          amount = i;
        }
      }
    }
  }

  uint32_t max_cost = table[w][amount];
  uint32_t min_weight = w;

  for (uint32_t i = 0; i <= w; i++) {
    for (uint32_t j = 0; j <= n; j++) {
      std::cout << table[i][j] << " ";
    }
    std::cout << "\n";
  }

  std::cout << max_cost << " " << min_weight;

  delete[] flat;
  for (uint32_t i = 0; i <= w; i++) {
    delete[] table[i];
  }
  delete[] table;

  return 0;
}
