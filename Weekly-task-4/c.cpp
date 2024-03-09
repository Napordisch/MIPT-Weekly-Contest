#include <iostream>
#include <cmath>
bool IsPrime(uint32_t number) {
  for (uint32_t i = 2; i <= std::pow(number, 0.5); i++) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  uint32_t number;
  std::cin >> number;
  if (IsPrime(number)) {
    std::cout << "prime";
  } else {
    std::cout << "composite";
  }
}