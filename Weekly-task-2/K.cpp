#include <iostream>

int main() {
  int32_t a, b, dvdr;
  std::cin >> a >> b;
  int32_t at = a;
  int32_t bt = b;
  while (at != 0 && bt != 0) {
    if (bt > at) {
      bt = bt % at;
    } else {
      at = at % bt;
    }
  }
  if (at == 0) {
    dvdr = bt;
  } else {
    dvdr = at;
  }
  std::cout << a / dvdr << " " << b / dvdr;
}