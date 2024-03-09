#include <iostream>

void Merge(const uint32_t* l, uint32_t l_len, const uint32_t* r, uint32_t r_len,
           uint32_t* buffer) {
  uint32_t l_index = 0;
  uint32_t r_index = 0;
  // with comparison
  while (l_index < l_len && r_index < r_len) {
    if (l[l_index] <= r[r_index]) {
      buffer[l_index + r_index] = l[l_index];
      l_index++;
    } else {
      buffer[l_index + r_index] = r[r_index];
      r_index++;
    }
  }
  // if r_len > l_len or l_len > r_len
  while (l_index < l_len) {
    buffer[l_index + r_index] = l[l_index];
    l_index++;
  }
  while (r_index < r_len) {
    buffer[l_index + r_index] = r[r_index];
    r_index++;
  }
}

void RecursiveMergeSort(uint32_t* arr, uint32_t n, uint32_t* buffer) {
  if (n <= 1) {
    return;
  }
  uint32_t middle = n / 2;
  RecursiveMergeSort(arr, middle, buffer);
  RecursiveMergeSort(arr + middle, n - middle, buffer);
  Merge(arr, middle, arr + middle, n - middle, buffer);
  for (uint32_t i = 0; i < n; i++) {
    arr[i] = buffer[i];
  }
}

void MergeSort(uint* arr, uint32_t n) {
  auto* buffer = new uint32_t[n];
  RecursiveMergeSort(arr, n, buffer);

  delete[] buffer;
}

int main() {
  using std::cin;
  using std::cout;

  uint32_t max_capacity, n;
  cin >> max_capacity >> n;
  uint32_t capacity = max_capacity;

  auto* weights = new uint32_t[n];
  for (uint32_t i = 0; i < n; i++) {
    cin >> weights[i];
  }

  MergeSort(weights, n);
  uint32_t chosen = 0;
  for (uint32_t i = 0; i < n; i++) {
    uint32_t cur_weight = weights[i];
    if (cur_weight <= capacity) {
      capacity -= cur_weight;
      chosen++;
    }
  }

  auto* backpack = new uint32_t[n];
  for (uint32_t i = 0; i < chosen; i++) {
    backpack[i] = weights[i];
  }

  uint32_t i = chosen;
  uint32_t temp_capacity = capacity + weights[i - 1];
  while (weights[i] <= temp_capacity) {
    i++;
  }
  capacity = temp_capacity - weights[i - 1];
  backpack[chosen - 1] = weights[i - 1];
  cout << chosen << " " << max_capacity - capacity;

  delete[] backpack;
  delete[] weights;
  return 0;
}