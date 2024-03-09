#include <iostream>

int main() {
  using std::cin;
  using std::cout;
  using std::string;
  string brackets;
  cin >> brackets;
  size_t n = brackets.size();
  uint32_t opening_brackets = 0;
  uint32_t wrong_closing_brackets = 0;
  for (size_t i = 0; i < n; i++) {
    if (brackets[i] == '(') {
      opening_brackets++;
    }
    if (brackets[i] == ')') {
      if (opening_brackets == 0) {
        wrong_closing_brackets++;
      } else {
        opening_brackets--;
      }
    }
  }
  cout << opening_brackets + wrong_closing_brackets;
  return 0;
}
