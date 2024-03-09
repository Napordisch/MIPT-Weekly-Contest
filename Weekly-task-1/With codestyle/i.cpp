#include <iostream>
#include <cmath>

int main() {
  float h, a, b;
  std::cin >> h >> a >> b;
  std::cout << ceil((h - a) / (a - b)) + 1;
}