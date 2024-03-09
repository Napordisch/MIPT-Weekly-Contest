#include <iostream>

uint32_t FibonacciTerm(uint32_t n, uint32_t cur = 1, uint32_t prev = 0) {
  if (n == 0) {
    return prev;
  }
  return FibonacciTerm(n - 1, cur + prev, cur);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  uint32_t n;
  std::cin >> n;
  std::cout << FibonacciTerm(n) * 2 - 1;
  return 0;
}