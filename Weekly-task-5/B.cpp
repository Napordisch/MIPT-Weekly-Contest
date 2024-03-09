#include <iostream>

void RevOut(uint32_t n, uint32_t counter = 0) {
  if (counter == n) {
    return;
  }
  int32_t a;
  std::cin >> a;
  RevOut(n, counter + 1);
  std::cout << a << " ";
}

int main() {
  uint32_t n;
  std::cin >> n;
  RevOut(n);
}