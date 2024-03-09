#include <iostream>

void SelectionSort(int32_t *array, uint32_t n) {
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = i + 1; j < n; j++) {
      if (array[i] > array[j]) {
        int32_t t = array[i];
        array[i] = array[j];
        array[j] = t;
      }
    }
  }
}

int main() {
  uint32_t n;
  std::cin >> n;
  int32_t *numbers = new int32_t[n];
  for (uint32_t i = 0; i < n; i++) {
    std::cin >> numbers[i];
  }
  SelectionSort(numbers, n);
  for (uint32_t i = 0; i < n; i++) {
    std::cout << numbers[i] << " ";
  }
  return 0;
  delete[] numbers;
}