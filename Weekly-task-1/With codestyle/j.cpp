#include <iostream>
//#include <cmath>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::cout << (n % m) * (m % n) + 1;
}