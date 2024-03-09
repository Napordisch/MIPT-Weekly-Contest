#include <iostream>

std::string Isleap(int year) {
  if (year % 400 == 0) {
    return "YES";
  }
  if (year % 100 == 0) {
    return "NO";
  }
  if (year % 4 == 0) {
    return "YES";
  }
  return "NO";
}

int main() {
  int year;
  std::cin >> year;
  std::cout << Isleap(year);
}