#include <iostream>
#include <cmath>
int main() {
  int a, b, c, max;
  std::cin >> a >> b >> c;
  if (a > b) {
    max = a;
  } else {
    max = b;
  }

  if (max > c) {
    std::cout << max;
  } else {
    std::cout << c;
  }
}
