#include <iostream>

int main() {
  bool *penis = new bool[5]{1};
  for (size_t i = 0; i < 5; i++)  {
    std::cout << penis[i];
  }
}