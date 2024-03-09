#include <iostream>
#include <cstdint>

using std::cin;
using std::cout;

int main() {
  std::uint32_t n = 0;
  std::uint32_t k = 0;
  cin >> n;
  auto sums = new std::uint32_t*[n];
  sums[0] = new std::uint32_t[n];
  for (std::uint32_t j = 0; j < n; j++) {
    cin >> sums[0][j];
  }
  cin >> k;
  auto queries = new uint32_t*[k];
  auto lengths = new uint32_t[n]{0};
  std::uint32_t max_start = 0;
  std::uint32_t max_len = 0;
  for (std::uint32_t i = 0; i < k; i++) {
    std::uint32_t start = 0;
    std::uint32_t end = 0;
    cin >> start >> end;
    queries[i] = new uint32_t[2];
    queries[i][0] = start - 1;
    queries[i][1] = end - start + 1;
    if (start - 1 > max_start) {
      max_start = start - 1;
    }
    if (end - start + 1 > max_len) {
      max_len = end - start + 1;
    }
  }

  for (std::uint32_t i = 1; i < max_len; i++) {
    std::uint32_t start_limit;
    if (max_len < n - i) {
      start_limit = max_len;
    } else {
      start_limit = n - i;
    }
    sums[i] = new std::uint32_t[start_limit];
    for (std::uint32_t j = 0; j < start_limit; j++) {
      sums[i][j] = static_cast<std::uint32_t>(sums[i - 1][j] + sums[0][j + i]);
    }
  }

  for (std::uint32_t i = 0; i < k; i++) {
    cout << sums[queries[i][1]][queries[i][0]];
  }

  for (std::uint32_t i = 0; i < n; i++) {
    delete[] sums[i];
  }
  for (std::uint32_t i = 0; i < k; i++) {
    delete[] queries[i];
  }
  delete[] sums;
  delete[] queries;
  return 0;
}

