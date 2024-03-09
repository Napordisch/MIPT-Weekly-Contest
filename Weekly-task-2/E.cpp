#include <iostream>

int main() {
  int x;
  std::cin >> x;

  for (int i = 2; i <= x; i++) {
    if (x % i == 0) {
      std::cout << i;
      break;
    }
  }
}