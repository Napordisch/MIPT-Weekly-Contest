#include <iostream>

int main() {
  int n;
  std::cin >> n;
  //
  for (int row = 0; row < n; row++) {
    for (int column = 0; column < n; column++){
      if (row + column == n-1) {
        std::cout << 1;
      } else if (row + column < n-1) {
        std::cout << 0;
      } else {
        std::cout << 2;
      }
      if (column < n - 1){
        std::cout << " ";
      } else {
        std::cout << "\n";
      }
    }
  }
}