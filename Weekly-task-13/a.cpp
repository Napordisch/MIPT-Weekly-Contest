#include <iostream>

using std::cin;
using std::cout;

auto max(auto a, auto b) {
  if (a > b) {
    return a;
  }
  return b;
}

// void lcs(int *dp, int *a, int *b, size_t n, size_t m) {
//   for (size_t i = 1; i < n; i++) {
//     for (size_t j = 1; j < m; j++) {
//       dp[i * m + j] = max(dp[(i - 1) * m + j], dp[(i * m) + j - 1]);
//       if (a[i] == b[j]) {
//         dp[i * m + j] = max(dp[(i - 1) * m + j - 1] + 1, dp[i * m + j]);
//       }
//     }
//   }
// }

void lcs(int **dp, int *a, int *b, size_t n, size_t m, auto **prev) {
  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= m; j++) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        prev[i][j] = std::make_pair(i - 1, j - 1);
      } else {
        if (dp[i - 1][j] > dp[i][j - 1]) {
          dp[i][j] = dp[i - 1][j];
          prev[i][j] = std::make_pair(i - 1, j);
        } else {
          dp[i][j] = dp[i][j - 1];
          prev[i][j] = std::make_pair(i, j - 1);
        }
      }
    }
  }
}

void PrintLCS(int **dp, std::pair<size_t, size_t> **prev, int *a, int *b, size_t i, size_t j) {
  if (i == 0 || j == 0) {
    return;
  }
  if (prev[i][j] == std::make_pair(i - 1, j - 1)) {
    PrintLCS(dp, prev, a, b, i - 1, j - 1);
    std::cout << a[i] << " ";
  } else {
    if (prev[i][j] == std::make_pair(i - 1, j)) {
      PrintLCS(dp, prev, a, b, i - 1, j);
    } else {
      PrintLCS(dp, prev, a, b, i, j - 1);
    }
  }
}

int main() {
  size_t n, m;
  cin >> n;
  int *a = new int[n];
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  cin >> m;
  int *b = new int[m];
  for (size_t j = 0; j < m; j++) {
    cin >> b[j];
  }

  int **dp = new int *[n + 1];
  for (size_t i = 0; i <= n; i++) {
    dp[i] = new int[m + 1]{0};
  }

  auto **prev = new std::pair<size_t, size_t> *[n + 1];
  for (int i = 0; i <= n; i++) {
    prev[i] = new std::pair<size_t, size_t>[m + 1];
  }
  
  int sz = dp[n][m];
  int idx = sz - 1;
  int c[sz];
  int x = n;
  int y = m;
  while (x > 0 && y > 0) {
    if (prev[x][y] == 0) {
      x--;
      continue;
    }
    if (prev[x][y] == 1) {
      y--;
      continue;
    }

    c[idx] = a[x - 1];
    x--;
    y--;
    idx--;
  }

  cout << dp[n][m] << '\n';
  for (int i = 0; i < sz; i++) {
    cout << c[i] << ' ';
  }
  return 0;
  lcs(dp, a, b, n, m, prev);
  //cout << dp[n * m - 1];
  for (size_t i = 0; i <= n; i++) {
    for (size_t j = 0; j <= m; j++) {
      cout << dp [i][j] << " ";
    }
    cout << "\n";
  }
  // PrintLCS(dp, prev, a, b, n, m);
}
