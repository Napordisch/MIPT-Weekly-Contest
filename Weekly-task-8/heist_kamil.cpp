#include <iostream>

void TableFunction(int** table, int const* flat_p, int const* flat_w, int w,
                   int n) {
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < w; ++j) {
      int t;

      table[i][j] = table[i - 1][j];
      if (flat_w[i - 1] <= j) {
        t = table[i - 1][j - flat_w[i - 1]] + flat_p[i - 1];

        if (t > table[i][j]) {
          table[i][j] = t;
        }
      }
    }
  }
}

void Tablefication(int** table, int w, int n) {
  int best = table[n - 1][w - 1];
  for (int j = w - 2; j > -1; --j) {
    if (table[n - 1][j] != best) {
      std::cout << table[n - 1][j + 1] << ' ' << j + 1;
      return;
    }
  }
}

int main() {
  int w, n;
  std::cin >> w >> n;

  int* arr_w = new int[n];
  int* arr_p = new int[n];

  int** table = new int*[n];
  for (int i = 0; i < n; i++) {
    table[i] = new int[w];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < w; ++j) {
      table[i][j] = 0;
    }
  }

  for (int i = 0; i < n; ++i) {
    std::cin >> arr_p[i] >> arr_w[i];
  }

  TableFunction(table, arr_p, arr_w, w, n);
  Tablefication(table, w, n);

  delete[] arr_p;
  delete[] arr_w;
  for (int i = 0; i < n; i++) {
    delete[] table[i];
  }
  delete[] table;
  return 0;
}