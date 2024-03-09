#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int a = 0;
  int b = 1;
  int c = 0;
  if (n >= 2) {
    for (int i = 2; i <= n; i++) {
      int c = a + b;
      a = b;
      b = c;
    }
  } else if (n == 0) {
    b = 0;
  } else if (n == 1) {
    b = 1;
  }
  std::cout << b;
}