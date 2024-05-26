#include <iostream>
#include <string>
#include <vector>

void PrintZFunctionForString(const std::string &s) {
  unsigned int length = s.size();
  unsigned int l = 0;
  unsigned int r = 0;
  std::vector<unsigned int> z(length, 0);
  z[0] = length;

  for (unsigned int i = 1; i < length; ++i) {
    if (i <= r) {
      z[i] = std::min(z[i - l], r - i + 1);
    }

    while (i + z[i] < length && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }

    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }

  for (unsigned int i = 0; i < z.size(); ++i) {
    std::cout << z[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  PrintZFunctionForString(s);
}