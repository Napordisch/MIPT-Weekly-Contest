#include <iostream>
#include <unordered_map>

int main() {
  unsigned int n = 0;
  std::cin >> n;
  std::unordered_map<unsigned int, unsigned int> colours;
  colours.reserve(n);

  for (unsigned int i = 0; i < n; ++i) {
    int colour_number = 0;
    std::cin >> colour_number;
    ++colours[colour_number];
  }

  unsigned int m = 0;
  std::cin >> m;

  for (unsigned int i = 0; i < m; ++i) {
    int colour_number = 0;
    std::cin >> colour_number;
    std::cout << colours[colour_number] << '\n';
  }
}