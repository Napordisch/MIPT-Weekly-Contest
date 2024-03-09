#include <iostream>

int main() {
  int v, t;
  std::cin >> v >> t;
  std::cout << (109 + ((v * t) - ((v * t) / 109) * 109)) % 109;
}