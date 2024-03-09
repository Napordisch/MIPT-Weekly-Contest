#include <iostream>

using std::cin;
using std::cout;

void Lcs(int **dp, int **prev, int *a, int *b, int m, int n) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (dp[i - 1][j] > dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        prev[i][j] = 0;
      } else {
        dp[i][j] = dp[i][j - 1];
        prev[i][j] = 1;
      }

      if (a[i - 1] == b[j - 1]) {
        prev[i][j] = 2;
        dp[i][j] = dp[i - 1][j - 1] + 1;
      }
    }
  }
}

void PrintLCS(int **prev, int *a, int n, int m, int sz) {
  int ids = sz - 1;
  auto *c = new int[sz];
  int i = n;
  int j = m;

  while (i > 0 && j > 0) {
    if (prev[i][j] == 0) {
      i--;
      continue;
    }
    if (prev[i][j] == 1) {
      j--;
      continue;
    }

    c[ids] = a[i - 1];
    i--;
    j--;
    ids--;
  }

  for (i = 0; i < sz; i++) {
    cout << c[i] << ' ';
  }
  delete[] c;
}

int main() {
  int n, m;

  cin >> n;
  auto a = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  cin >> m;
  auto b = new int[m];
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  auto **dp = new int *[n + 1];
  for (int i = 0; i <= n; i++) {
    dp[i] = new int[m + 1]{};
  }

  auto **prev = new int *[n + 1];
  for (int i = 0; i <= n; i++) {
    prev[i] = new int[m + 1];
  }
  Lcs(dp, prev, a, b, m, n);
  PrintLCS(prev, a, n, m, dp[n][m]);

  for (int i = 0; i < n + 1; i++) {
    delete[] dp[i];
  }
  for (int i = 0; i < n + 1; i++) {
    delete[] prev[i];
  }
  delete[] dp;
  delete[] prev;
  delete[] a;
  delete[] b;
  return 0;
}