#include <iostream>

int Gcd(uint32_t a, uint32_t b) {
  if (b == 0) {
    return a;
  }
  return Gcd(b, a % b);
}

int main() {
  uint32_t n, a, b;
  std::cin >> n >> a >> b;
  uint32_t current_gcd = Gcd(a, b);
  for (uint32_t i = 0; i < n - 2; i++) {
    uint32_t x;
    std::cin >> x;
    current_gcd = Gcd(x, current_gcd);
  }
  std::cout << current_gcd;
}