#include <iostream>

int main() {
  using std::cin;
  using std::cout;
  std::string s = "abcd*de*";
  size_t n = s.size();
  for (size_t i = 0; i < n; i++) {
    if (s[i] == '*') {
      cout << s[i];
    }
  }
}