#include <iostream>
//#include <cmath>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::cout << (n > m) * n + (m > n) * m + (m == n) * m;
}