#include <iostream>

int main() {
  int64_t x, y;
  std::cin >> x >> y;
  int64_t a = x;
  int64_t b = y;
  while (a != 0 && b != 0 a) {
    if (a > b) {
      a = a % b;
    } else {
      b = b % a;
    }
  }
  int64_t gcd;
  if (b == 0) {
    gcd = a;
  } else {
    gcd = b;
  }
  std::cout << gcd << " " << (x * y) / gcd;
}