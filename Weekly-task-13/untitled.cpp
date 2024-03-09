void lcs(int **dp)

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

  int **dp = new int *[n + 1];
  for (int i = 0; i <= n; i++) {
    dp[i] = new int[n + 1]{};
  }

  int **prev = new int *[n + 1];
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
