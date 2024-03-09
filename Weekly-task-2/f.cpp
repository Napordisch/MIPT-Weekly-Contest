#include <iostream>

int main() {
  int n, sum;
  sum = 0;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    int x;
    std::cin >> x;
    sum += x;
  }
  std::cout << sum;
}