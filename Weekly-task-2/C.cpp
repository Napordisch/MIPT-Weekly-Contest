#include <iostream>

int main(){
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
  if ((a % c == b % d) && (b % d == 0)) {
    std::cout << "NO";
  } else if ((a != 0) && (b % a == 0)) {
    std::cout << - b / a;
  } else if (a == b && b == 0) {
    std::cout << "INF";
  }
}