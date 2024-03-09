#include <iostream>

int main() {
  int32_t n, m;
  std::cin >> n >> m;
  int32_t row_num = 0;
  int32_t row_num_diff = 1;
  int32_t start_col_numdiff = row_num_diff;
  int32_t start_col_numdiff_pos = row_num;
  for (int row = 0; row < n; row++) {
    int32_t col_num = row_num;
    int32_t col_numdiff_pos = start_col_numdiff_pos;
    int32_t col_numdiff = start_col_numdiff;
    for (int32_t column = 0; column < m; column++) {
      col_numdiff = start_col_numdiff;
      std::cout << col_num;
      col_num += col_numdiff;
      if (column < m - 1) {
        std::cout << " ";
      }
      if (col_numdiff_pos < n - 1) {
        col_numdiff++;
      } else if (col_numdiff_pos > n - 1) {
        col_numdiff--;
      }
    }
    if (row == n - 1) {
      break;
    }
    std::cout << "\n";
    row_num_diff++;
    row_num += row_num_diff;
    if (row < n - 2) {
      start_col_numdiff++;
    } else if (row < n - 2) {
      start_col_numdiff--;
    }
    start_col_numdiff_pos++;
  }
}