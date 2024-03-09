#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;
  int k = 1;
  while (a != b && a > 0 && b > 0) {
    // uint32_t min_side = (a > b) * b + (b > a) * a;
    if (a > b) {
      a -= b;
    } else if (b > a) {
      b -= a;
    }
    k++;
  }
  std::cout << k;
}