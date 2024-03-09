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
  for (std::uint32_t i = 1; i < n; i++) {
    sums[i] = new std::uint32_t[n - i];
    for (std::uint32_t j = 0; j < n - i; j++) {
      sums[i][j] = static_cast<std::uint32_t>(sums[i - 1][j] + sums[0][j + i]);
    }
  }

  cin >> k;
  for (std::uint32_t i = 0; i < k; i++) {
    std::uint32_t start = 0;
    std::uint32_t end = 0;
    cin >> start >> end;
    cout << sums[end - start][start - 1] << " ";
  }
  for (std::uint32_t i = 0; i < n; i++) {
    delete[] sums[i];
  }
  delete[] sums;
  return 0;
}
