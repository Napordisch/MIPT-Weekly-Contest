#include <iostream>

double FPow(double a, int64_t n) {
  if (n < 0) {
    return FPow(1 / a, -n);
  }
  if (n == 0) {
    return 1;
  }
  if (n % 2 == 0) {
    return FPow(a * a, n / 2);
  }
  if (n % 2) {
    return a * FPow(a * a, (n - 1) / 2);
  }
  return a;
}

int main() {
  double a;
  int64_t n;
  std::cin >> a >> n;
  std::cout << FPow(a, n);
  return 0;
}