#include <iostream>
int abs(int number) {
  if (number < 0) {
    return -number;
  }
  return number;
}
int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return abs(a);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b);
  return 0;
}