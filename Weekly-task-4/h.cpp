#include <iostream>

void InsertionSort(int32_t *arr, size_t arr_size) {
  for (size_t i = 0; i < arr_size - 1; i++) {
    size_t j = i + 1;
    while (j > 0 && arr[j - 1] > arr[j]) {
      int32_t t = arr[j - 1];
      arr[j - 1] = arr[j];
      arr[j] = t;
      j = j - 1;
    }
  }
}

int main() {
  size_t n;
  std::cin >> n;
  int32_t *arr = new int32_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  InsertionSort(arr, n);

  // output
  for (size_t i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  return 0;
}