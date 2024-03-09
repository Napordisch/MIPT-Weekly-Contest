#include <iostream>

size_t Partition(int32_t *arr, size_t left, size_t right){
  size_t pivot = arr[left];
  size_t l = left;
  size_t r = right;
  // for (size_t i = left; i < right; i++) {
  //   std::cout << arr[i] << " ";
  // }
  while (l < r) {
    while (arr[l] < pivot) {
      l++;
      std::cout << "pivot: " << pivot << "\n";
      std::cout << "l: " << l << "\n";
    }
    while (arr[right] > pivot) {
      r--;
      std::cout << "pivot: " << pivot << "\n";
      std::cout << "r: " << r << "\n";
    }
    if (l <= r) {
      int32_t t = r;
      l = r;
      r = t;
    }
  }
  return r;
}

void QuickSort(int32_t *arr, size_t left, size_t right){
  if (right <= left) {
    return;
  }
  size_t p = Partition(arr, left, right);
  QuickSort(arr, left, p - 1);
  QuickSort(arr, p + 1, right);
}

int main() {
  size_t n;
  std::cin >> n;
  int32_t *arr = new int32_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  QuickSort(arr, 0, n - 1);
  for (size_t i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
}