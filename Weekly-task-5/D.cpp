#include <iostream>

void FibonacciCount(uint32_t n, uint32_t *counter) {
  *counter += 1;
  if (n <= 2) {
    return;
  }
  FibonacciCount(n - 2, counter);
  FibonacciCount(n - 1, counter);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  uint32_t n;
  std::cin >> n;
  uint32_t counter = 0;
  FibonacciCount(n, &counter);
  std::cout << counter;
  return 0;
}