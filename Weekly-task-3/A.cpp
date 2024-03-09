#include <iostream>

int main() {
  uint32_t n;
  std::cin >> n;
  uint32_t **arr = new uint32_t *[n];
  for (uint32_t i = 0; i < n; i++) {
    arr[i] = new uint32_t[n];
  }
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < n; j++) {
      // std::cout << i << j;
      if (i + j == n - 1) {
        arr[i][j] = 1;
      } else if (i + j < n - 1) {
        arr[i][j] = 0;
      } else {
        arr[i][j] = 2;
      }
    }
  }
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < n; j++) {
      std::cout << arr[i][j];
      if (j < n - 1) {
        std::cout << " ";
      } else if (i < n - 1) {
        std::cout << "\n";
      }
    }
  }
  for (uint32_t i = 0; i < n; i++) {
    delete[] arr[i];
  }
  delete[] arr;
  return 0;
}