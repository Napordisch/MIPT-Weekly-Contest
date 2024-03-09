#include <iostream>
#include <cstdlib>

size_t Partition(int32_t *arr, size_t n, int32_t partition_count) {
  // std::cout << "\n";
  // std::cout << "Array in partition " << partition_count << ":\n";
  // for (size_t i = 0; i < n; i++) {
  //   std::cout << arr[i] << " ";
  // }
  // std::cout << "\n";
  size_t i = 0;
  size_t j = n - 1;
  // std::cout << "i: " << i << "\tarr[i]: " << arr[i] << "\tj: " << j << "\tarr[j]: " << arr[j] << "\n";

  // int32_t pivot = arr[((i + n) / 2)];
  int32_t pivot = arr[j];
  while (i < j) {
    // std::cout << "\n";
    // std::cout << "partition_count: " << partition_count << "\ti: " << i << "\tarr[i]: " << arr[i] << "\tj: " 
    // << j << "\tarr[j]: " << arr[j] << "\tpivot: " << pivot << "\n";
    // std::cout << "\n";
    
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
  // std::cout << "i: " << i << "\n";
  return i;
}

void QuickSort(int32_t *arr, size_t n, int32_t partition_count) {
  // std::cout << "first n in Quicksort: " << n<< "\n";
  // std::cout << "Array in quicksort " << ":\n";
  // for (size_t i = 0; i < n; i++) {
  //   std::cout << arr[i] << " ";
  // }
  // std::cout << "\n";
  
  if (n <= 1) return;
  // std::cout << "\n";

  // int32_t pivot = arr[rand() % n];
  // std::cout << "pivot: " << pivot << "\n";
  size_t i = Partition(arr, n, partition_count);
  // std::cout << "\n";
  // std::cout << "i after partition: "<< i << "\n";
  // std::cout << "\n";
  partition_count++;


  QuickSort(arr, i, partition_count);
  QuickSort(arr + i, n - i, partition_count);
}

int main() {
  size_t n;
  std::cin >> n;
  uint32_t partition_count = 1;
  int32_t *arr = new int32_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  QuickSort(arr, n , partition_count);
  for (size_t i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  return 0;
}