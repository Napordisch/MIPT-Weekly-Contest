#include <iostream>

int main() {
  uint32_t n;
  std::cin >> n;
  int32_t spiral[51 * 51]{};
  for (uint32_t i = 0; i < n * n; i++) {
    spiral[i] = 0;
  }
  uint32_t row = ok0;
  uint32_t col = 0;
  while (true) {
    uint32_t steps = 0;
    //  col →
    while (true) {
      spiral[row * n + col] = 1;
      steps++;
      if (col < n - 2) {
        if (spiral[row * n + col + 2] == 1) {
          break;
        }
      }
      if (col == n - 1) {
        break;
      }
      col++;
    }
    if (steps < 3) {
      break;
    }
    steps = 0;
    //  row ↓
    while (true) {
      spiral[row * n + col] = 1;
      steps++;
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
    if (steps < 3) {
      break;
    }
    steps = 0;
    // col ←
    while (true) {
      spiral[row * n + col] = 1;
      steps++;
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
    if (steps < 3) {
      break;
    }
    steps = 0;
    // row ↑
    while (true) {
      spiral[row * n + col] = 1;
      steps++;
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
    if (steps < 3) {
      break;
    }
  }
  for (uint32_t j = 0; j < n; j++) {
    for (uint32_t i = 0; i < n; i++) {
      std::cout << spiral[j * n + i];
    }
    std::cout << "\n";
  }
}