#include <iostream>
#include "cstring.cpp"

int main() {
  char a[] = {'a', 'b', 'c', '\0'};
  char b[] = {'\0'};
  char c[] = {'a', 'b', '\0'};

  //std::cout << Strstr(b, b)[0];
  std::cout << (Strstr(a, b) == nullptr) << "\n";
  std::cout << Strstr(a, b) << "\n";
}
