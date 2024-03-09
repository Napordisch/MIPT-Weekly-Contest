#include <cstdlib>
#include <iostream>

int32_t Partition(int32_t* arr, size_t n) {
  size_t i = 0;
  size_t j = n - 1;

  int32_t pivot = arr[rand() % n];
  while (i < j) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i < j) {
      int32_t t = arr[i];
      arr[i] = arr[j];
      arr[j] = t;
      i++;
      j--;
    }
  }
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