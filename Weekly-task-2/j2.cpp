#include <iostream>

int main() {
  uint32_t a, b;
  std::cin >> a >> b;
  uint32_t k = 0;
  while (a != 0 && b != 0) {
    if (a > b) {
      k += a / b;
      a %= b;
    } else {
      k += b / a;
      b %= a;
    }
  }
  std::cout << k;
}