#include <iostream>

int main() {
  uint32_t m, n;
  std::cin >> n >> m;
  uint32_t *arr = new uint32_t[n * m];
  for (uint32_t i = 0; i < m; i++) {
    arr[i] = 1;
  }
  std::cout << "\n";
  for (uint32_t i = 0; i < n; i++) {
    arr[i * m] = 1;
  }
  std::cout << "\n";
  for (uint32_t i = 1; i < n; i++) {
    for (uint32_t j = 1; j < m; j++) {
      arr[i * m + j] = arr[(i - 1) * m + j] + arr[i * m + (j - 1)];
    }
  }
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < m; j++) {
      std::cout << arr[i * m + j];
      if (j < m - 1) {
        std::cout << " ";
      }
    }
    if (i < n - 1) {
      std::cout << "\n";
    }
  }
  delete[] arr;
}