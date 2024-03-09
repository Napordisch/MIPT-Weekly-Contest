#include <iostream>

int main() {
  uint32_t a, b;
  std::cin >> a >> b;
  uint32_t k = 1;
  while (a != b && a > 0 && b > 0) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
    k++;
  }
  std::cout << k;
}