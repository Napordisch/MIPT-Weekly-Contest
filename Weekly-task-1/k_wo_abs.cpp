#include <iostream>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::cout << (m + n + abs(m - n)) / 2;
}