#include <iostream>

int main() {
  uint32_t n;
  std::cin >> n;
  int32_t *array = new int32_t[n + 1];
  for (uint32_t i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  int32_t inserted_number;
  uint32_t index;
  std::cin >> inserted_number >> index;

  // creating the gap for the inserted number
  for (uint32_t i = n; i > index - 1; i--) {
    array[i] = array[i - 1];
  }

  array[index - 1] = inserted_number;

  // output
  for (uint32_t i = 0; i < n + 1; i++) {
    std::cout << array[i] << " ";
  }

  delete[] array;
  return 0;
}