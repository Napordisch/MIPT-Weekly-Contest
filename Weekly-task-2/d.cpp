#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << "\n";
  if (a % 2 != 0) {
    a += 1;
  }
  for (int i = a; i <= b; i += 2) {
    std::cout << i << " ";
  }
}