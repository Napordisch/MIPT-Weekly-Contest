#include <iostream>

int main() {
  uint32_t n, m, w;
  std::cin >> n >> m >> w;
  bool *field = new bool[n * m];
  for (uint32_t i = 0; i < n * m; i++) {
    field[i] = false;
  }
  for (uint32_t mine = 0; mine < w; mine++) {
    uint32_t x, y;
    std::cin >> y >> x;
    x--;
    y--;
    field[y * m + x] = true;
  }
  for (uint32_t j = 0; j < n; j++) {
    for (uint32_t i = 0; i < m; i++) {
      if (field[j * m + i]) {
        std::cout << "*";
        std::cout << " ";
      } else {
        uint32_t mines = 0;
        int32_t xs = -1;
        int32_t xe = 1;
        int32_t ys = -1;
        int32_t ye = 1;
        if (i == 0) {
          xs = 0;
        } else if (i == m - 1) {
          xe = 0;
        }
        if (j == 0) {
          ys = 0;
        } else if (j == n - 1) {
          ye = 0;
        }
        for (int32_t y = ys; y <= ye; y++) {
          for (int32_t x = xs; x <= xe; x++) {
            if (field[(j + y) * m + (i + x)]) {
              mines++;
            }
          }
        }
        std::cout << mines;
        std::cout << " ";
      }
    }
    if (j < n - 1) {
      std::cout << "\n";
    }
  }
  delete[] field;
}