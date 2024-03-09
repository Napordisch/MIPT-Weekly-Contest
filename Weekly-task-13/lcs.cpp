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
