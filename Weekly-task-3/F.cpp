#include <iostream>

int main() {
  uint32_t n;
  std::cin >> n;
  uint32_t *spiral = new uint32_t[n * n];
  uint32_t row = 0;
  uint32_t col = 0;
  while (true) {
    //  col →
    while (true) {  
      spiral[row * n + col] = 1;
      if (col < n - 2) {
        if (spiral[row * n + col +  2] == 1) {
          break;
        }
      }
      if (col == n - 1) {
        break;
      }
      col++;
    }
    //  row ↓
    while (true) {  
      spiral[row * n + col] = 1;
      if (row < n - 2) {
        if (spiral[(row + 2) * n + col] == 1) {
          break;
        }
      } 
      if (row == n - 1) {
        break;
      }
      row++;
    }
    // col ←
    while (true) {
      spiral[row * n + col] = 1;
      if (col > 1) {
        if (spiral[row * n + col - 2] == 1) {
          break;
        }
      }
      if (col == 0) {
        break;
      }
      col--;
    }
    //  row ↑
    while (true) {  
      spiral[row * n + col] = 1;
      if (row > 1) {
        if (spiral[(row - 2) * n + col] == 1) {
          break;
        }
      }
      if (row == 0) {
        break;
      }
      row--;
    }
    if (row > 1 && col > 1 && col < n - 2 && row < n - 2) {
      if (spiral[(row - 2) * n + col] == 1 && spiral[row * n + col - 2] == 1 && spiral[row * n + col + 2] == 1 && spiral[(row + 2) * n + col] == 1){
        break;
      }
    }
  }
  for (uint32_t j = 0; j < n; j++) {
    for (uint32_t i = 0; i < n; i++) {
      std::cout << spiral[j * n + i];
      // if (i < n - 1) {
      //   std::cout << " ";
      // }
    }
    if (j < n - 1) {
      std::cout << "\n";
    }
  }
}