#include <iostream>

int main() {
  int32_t n;
  std::cin >> n;
  if (n % 3 == 0) {
    std::cout << 2;
  } else {
    std::cout << 1;
  }
  return 0;
}