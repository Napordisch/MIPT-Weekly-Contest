#include <iostream>

// int32_t RecursiveSum(int32_t s, int32_t counter, bool positive, b) {
//   static int32_t counter = 0;
//   static int32_t s = a;

//   if (counter == b) {
//     return s;
//   }

// }

int32_t Sum(int32_t a, int32_t b, int32_t counter = 0) {
  // std::cout << counter << b;
  int32_t s = a;

  if (counter == b) {
    return s;
  }

  s += (b > 0) - (b < 0);
  counter += (b > 0) - (b < 0);
  return Sum(s, b, counter);
}

int main() {
  int32_t a, b;
  std::cin >> a >> b;
  std::cout << Sum(a, b);

  return 0;
}