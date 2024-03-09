#include <iostream>
#include <cmath>

int main() {
  int h, a, b;
  std::cin >> h >> a >> b;
  std::cout << ((h - a) / (a - b)) + ((h - a) % (a - b) != 0) + 1;
}