#include <iostream>
#include <cmath>
int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << pow(pow(a, 2) + pow(b, 2), 0.5);
  return 0;
}