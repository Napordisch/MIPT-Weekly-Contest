#include <iostream>

int main() {
  int n, m, k;
  std::cin >> n >> m >> k;
  if (k % n == 0 && k / n <= m) {
    std::cout << "YES";
  } else if (k % m == 0 && k / m <= n) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}