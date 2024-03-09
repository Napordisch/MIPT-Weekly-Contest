#include <iostream>
#include <cmath>
#include <iomanip>

long double IntervalLength(long double x1, long double y1, long double x2, long double y2) {
  return std::pow((std::pow((y2 - y1), 2) + std::pow((x2 - x1), 2)), 0.5);
}

int main() {
  long double x1, x2, x3, y1, y2, y3;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  std::cout.precision(7);
  std::cout << IntervalLength(x1, y1, x2, y2) + IntervalLength(x2, y2, x3, y3) + IntervalLength(x3, y3, x1, y1);
}