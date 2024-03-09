#include <iostream>

void BubbleSort(int32_t *array, size_t array_size) {
  for (size_t i = 1; i < array_size; i++) {
    for (size_t j = 0; j < array_size - i; j++) {
      if (array[j] > array[j + 1]) {
        int32_t t = array[j];
        array[j] = array[j + 1];
        array[j + 1] = t;
      }
    }
  }
}

int main() {
  size_t n;
  std::cin >> n;
  int32_t *array = new int32_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  BubbleSort(array, n);

  for (size_t i = 0; i < n; i++) {
    std::cout << array[i] << " ";
  }
  delete[] array;
  return 0;
}