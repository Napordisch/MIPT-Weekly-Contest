#include <iostream>

int main() {
  uint32_t n;
  std::cin >> n;
  uint32_t *arr = new uint32_t[n * n];
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < n; j++) {
      // std::cout << i << j;
      if (i + j == n - 1) {
        arr[i * n + j] = 1;
      } else if (i + j < n - 1) {
        arr[i * n + j] = 0;
      } else {
        arr[i * n + j] = 2;
      }
    }
  }
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < n; j++) {
      std::cout << arr[i * n + j];
      if (j < n - 1) {
        std::cout << " ";
      } else if (i < n - 1) {
        std::cout << "\n";
      }
    }
  }
  delete[] arr;
  return 0;
}