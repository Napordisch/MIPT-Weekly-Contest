#include <iostream>
using std::cin;
using std::cout;

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

  auto dp = new int *[n + 1];
  for (int i = 0; i <= n; i++) {
    dp[i] = new int[n + 1]{};
  }

  auto **prev = new int *[n + 1];
  for (int i = 0; i <= n; i++) {
    prev[i] = new int[m + 1];
  }

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

  // for (int i = 0; i <= n; i++) {
  //   for (int j = 0; j <= m; j++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << "\n";
  // }
  int sz = dp[n][m];
  int idx = sz - 1;
  auto *c = new int[sz];
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

  for (int i = 0; i <= n; i++) {
    delete[] dp[i];
  }
  delete[] dp;

  for (int i = 0; i <= n; i++) {
    delete[] prev[i];
  }
  delete[] prev;
  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}