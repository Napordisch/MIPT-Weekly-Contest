#include <iostream>

int main() {
  uint32_t n, m;
  std::cin >> n >> m;
  uint32_t *results = new uint32_t[n * m];
  uint32_t max_r = 0;
  uint32_t maxs = 0;
  for (uint32_t i = 0; i < m * n; i++) {
    uint32_t r;
    std::cin >> r;
    results[i] = r;
    if (r == max_r) {
      maxs++;
    } else if (r > max_r) {
      maxs = 1;
      max_r = r;
    }
  }
  uint32_t *best_players = new uint32_t[maxs];
  uint32_t bpi = 0;
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < m; j++) {
      if (results[i * m + j] == max_r) {
        best_players[bpi] = i;
        bpi++;
        break;
      }
    }
  }
  std::cout << bpi << "\n";
  for (uint32_t i = 0; i < bpi; i++) {
    std::cout << best_players[i] << " ";
  }
  delete[] results;
  delete [] best_players;
  return 0;
}