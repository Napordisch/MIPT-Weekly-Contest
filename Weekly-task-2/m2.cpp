#include <iostream>

int main() {
  uint32_t n, m;
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << ((1 + (i - 1) + (j - 1) + 1) / 2) * ((i - 1) + (j - 1)) + j;
      if (j < m - 1) {
        std::cout << " ";
      }
    }
    if (i < n - 1) {
      std::cout << "\n";
    }
  }
}