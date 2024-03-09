#include <iostream>

int32_t Partition(int32_t* arr, size_t n) {
  int32_t pivot = arr[n - 1];

  size_t i = 0;

  for (size_t j = 0; j < n - 1; j++) {
    if (arr[j] <= pivot) {
      int32_t t = arr[j];
      arr[j] = arr[i];
      arr[i] = t;
      i++;
    }
  }
  int32_t t = arr[i];
  arr[i] = arr[n - 1];
  arr[n - 1] = t;
  return i;
}

void QuickSort(int32_t* arr, size_t n) {
  if (n <= 1) {
    return;
  }

  size_t i = Partition(arr, n);

  QuickSort(arr, i);
  QuickSort(arr + i, n - i);
}

int main() {
  size_t n;
  std::cin >> n;
  int32_t* arr = new int32_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  QuickSort(arr, n);
  for (size_t i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  return 0;
}