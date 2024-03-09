#include <iostream>

int main() {
  int i;
  std::cin >> i;
  std::cout << (i % 10) + ((i % 100) / 10) + i / 100;
}