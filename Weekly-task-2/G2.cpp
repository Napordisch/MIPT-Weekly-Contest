#include <iostream>

int main() {
  int max_1 = 0;
  int max_2 = 0;
  while (true) {
    int a;
    std::cin >> a;
    if (a == 0) {
      break;
    }
    max_2 = (a < max_1 && a > max_2) * a + max_1 * (a > max_1) + max_2 * (a < max_1 && a < max_2);
    max_1 = (a > max_1) * a + (a < max_1) * max_1;
    // std::cout << "max_1 = " << max_1 << "\nmax_2 = " << max_2 << "\n";
  }
  std::cout << max_2;
}