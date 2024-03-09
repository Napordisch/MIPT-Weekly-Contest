#include <iostream>
#include <cmath>

int main() {
  int h, a, b;
  std::cin >> h >> a >> b;
  std::cout << ((h - a) + (a - b) - 1 ) / (a - b) + 1;
}