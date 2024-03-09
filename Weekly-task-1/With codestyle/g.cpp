#include <iostream>

int main() {
  int h, m, s;
  std::cin >> s;
  // hours
  h = s / 3600;
  h = h - 24 * (h / 24);
  s = s % 3600;
  // minutes
  m = s / 60;
  s = s % 60;
  std::cout << h << ":" << m / 10 << m % 10 << ":" << s / 10 << s % 10;
}