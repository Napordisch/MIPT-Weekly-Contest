#include <iostream>

int main(){
  int32_t n, m;
  std::cin >> n >> m;

  int32_t *table = new int32_t[n * m];
  int32_t number = 0;
  for (int32_t istart = 0; istart < m; istart++) {
    int32_t i = istart;
    int32_t j = 0;
    while (i >= 0 && j != n) {
      table[j * m + i] = number;
      number++;
      i--;
      j++;
    }
  }
  for (int32_t jstart = 1; jstart < n; jstart++) {
    int32_t i = m - 1;
    int32_t j = jstart;
    while (i >= 0 && j != n) {
      table[j * m + i] = number;
      number++;
      i--;
      j++;
    }
  }
  for (int32_t j = 0; j < n; j++) {
    for (int32_t i = 0; i < m; i++) {
      std::cout << table[j * m + i];
      if (i < m - 1) {
        std::cout << " ";
      }
    }
    if (j < n - 1) {
      std::cout << "\n";
    }
  }
  delete[] table;

}