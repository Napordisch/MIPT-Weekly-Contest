#include <iostream>
#include <numeric>

int main() {
  uint32_t a, b;
  std::cin >> a >> b;
  uint32_t k = 0;
  uint32_t g = std::gcd(a, b);
  k = (a*b)/(g*g);
  std::cout << k;
}