#include <iostream>

uint32_t NumsAmnt(std::string s) {
  uint32_t amount = 0;
  for(uint32_t i = 0; i < s.length(); i++) {
    char c = s[i];
    if (c >= '0' && c <= '9') {
      amount++;
    }
  }
  return amount;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << NumsAmnt(s);
}