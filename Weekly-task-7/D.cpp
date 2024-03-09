#include <iostream>

int main() {
  int32_t n;
  std::cin >> n;
  auto* input_data = new int32_t[n];
  int32_t min = 0;
  int32_t max = 0;
  for (int32_t i = 0; i < n; i++) {
    std::cin >> input_data[i];
    if (input_data[i] < min) {
      min = input_data[i];
    }
    if (input_data[i] > max) {
      max = input_data[i];
    }
  }
  auto* counters = new int32_t[max - min + 1]{0};
  for (int32_t i = 0; i < n; i++) {
    counters[input_data[i] - min]++;
  }
  for (int32_t i = 0; i < max - min + 1; i++) {
    while (counters[i] > 0) {
      std::cout << i + min << "\n";
      counters[i]--;
    }
  }
  delete[] input_data;
  delete[] counters;
  return 0;
}