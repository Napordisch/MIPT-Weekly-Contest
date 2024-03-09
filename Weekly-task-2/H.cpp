#include <iostream>

int main() {
  uint64_t n;
  uint64_t sum = 0;
  std::cin >> n;
  while (true) {
    if (n / 10 == 0) {
      sum += (n % 10);
      break;
    }
    sum += n % 10;
    n /= 10;
  }
  std::cout << sum;
}