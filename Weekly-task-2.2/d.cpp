#include <iostream>

using std::cin;
using std::cout;

int main() {
  uint16_t n;
  cin >> n;
  uint16_t min_path = UINT16_MAX;
  uint16_t chosen[3];
  auto **table = new uint16_t *[n];
  for (uint16_t i = 0; i < n; ++i) {
    table[i] = new uint16_t[n];
    for (uint16_t j = 0; j < n; ++j) {
      cin >> table[i][j];
    }
  }

  for (uint16_t i = 0; i < n; ++i) {
    for (uint16_t j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }

      for (uint16_t k = 0; k < n; ++k) {
        if (j == k || k == i) {
          continue;
        }

        uint16_t first = table[i][j];
        uint16_t second = table[j][k];
        uint16_t third = table[k][i];
        uint16_t sum = first + second + third;
        if (sum < min_path) {
          chosen[0] = i;
          chosen[1] = j;
          chosen[2] = k;
          min_path = sum;
        }
      }
    }
  }

  cout << chosen[0] + 1 << " " << chosen[1] + 1 << " " << chosen[2] + 1;

  for (uint16_t i = 0; i < n; ++i) {
    delete[] table[i];
  }
  delete[] table;
  return 0;
}
