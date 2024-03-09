#include <iostream>

int main() {
  int32_t a, b;
  std::cin >> a >> b;
  int32_t at = (a > b) * a + (b > a) * b + (a == b) * a;
  int32_t bt = (a < b) * a + (b < a) * b + (a == b) * a;
  while (bt != 0) {
    int32_t t = at % bt;
    at = bt;
    bt = t;
  }
  int32_t dvdr = at + bt;
  int32_t c, d;
  if (dvdr != 0) {
    c = a / dvdr;
    d = b / dvdr;
  } else {
    c = a;
    d = b;
  }
  
  if (d > 0) {
    std::cout << c << " " << d;
  } else if (d < 0) {
    std::cout << -c << " " << -d;
  }
  return 0;
}