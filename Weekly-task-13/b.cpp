#include <iostream>

using std::cin;
using std::cout;

int main() {
  int n;

  cin >> n;
  auto a = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  auto *dp = new int[n]{0};
  auto *prev = new int[n]{0};

  for (int i = 0; i < n; i++) {
    dp[i] = 1;
    prev[i] = -1;
    for (int k = 0; k < i; k++) {
      if (dp[k] + 1 > dp[i] && a[k] < a[i]) {
        dp[i] = dp[k] + 1;
        prev[i] = k;
      }
    }
  }
  int max_dp = 0;
  int i_max_dp = 0;
  for (int i = 0; i < n; i++) {
    if (dp[i] > max_dp) {
      max_dp = dp[i];
      i_max_dp = i;
    }
  }

  {
    // i_max_dp = len of the sequence
    auto *lis = new int[max_dp];
    int i = i_max_dp;
    int j = max_dp - 1;
    while (i != -1) {
      lis[j] = a[i];
      j--;
      i = prev[i];
    }
    for (int o = 0; o < max_dp; o++) {
      cout << lis[o] << " ";
    }
    delete[] lis;
  }

  delete[] dp;
  delete[] prev;
  delete[] a;
  return 0;
}