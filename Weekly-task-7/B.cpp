#include <iostream>
#include <cmath>

void Swap(int32_t& a, int32_t& b) {
  int32_t t = a;
  a = b;
  b = t;
}

void SiftUp(int32_t* arr, int32_t id) {
  while (id > 0) {
    int32_t parent_id = (id - 1) / 2;
    if (arr[parent_id] < arr[id]) {
      Swap(arr[parent_id], arr[id]);
      id = parent_id;
    } else {
      break;
    }
  }
}

void SiftDown(int32_t* arr, int32_t size, int32_t id) {
  while (id < size) {
    int32_t left_child_id = id * 2 + 1;
    int32_t right_child_id = id * 2 + 2;
    int32_t max_id = id;
    if (left_child_id < size && arr[left_child_id] > arr[max_id]) {
      max_id = left_child_id;
    }
    if (right_child_id < size && arr[right_child_id] > arr[max_id]) {
      max_id = right_child_id;
    }
    if (id != max_id) {
      Swap(arr[id], arr[max_id]);
      id = max_id;
    } else {
      break;
    }
  }
}

int32_t ExtractMax(int32_t* arr, int32_t& size) {
  Swap(arr[0], arr[size - 1]);
  int32_t max = arr[size - 1];
  size--;
  SiftDown(arr, size, 0);
  return max;
}

void Resize(int32_t*& arr, int32_t& capacity) {
  auto* new_arr = new int32_t[2 * capacity];
  for (int32_t i = 0; i < capacity; i++) {
    new_arr[i] = arr[i];
  }
  delete[] arr;
  arr = new_arr;
  capacity = capacity * 2;
}

void Insert(int32_t*& arr, int32_t& size, int32_t& capacity, int32_t elem) {
  if (size >= capacity - 1) {
    Resize(arr, capacity);
  }
  size++;
  arr[size] = elem;
  SiftUp(arr, size);
}

int main() {
  int32_t n;
  std::cin >> n;
  int32_t size = n;
  auto* heap = new int32_t[size];
  int32_t capacity = size;
  auto* sorted = new int32_t[n];
  for (int32_t i = 0; i < n; i++) {
    int32_t elem;
    std::cin >> elem;
    Insert(heap, size, capacity, elem);
  }
  for (int32_t i = 0; i < n; i++) {
    sorted[i] = ExtractMax(heap, size);
  }
  for (int32_t i = n - 1; i >= 0; i--) {
    std::cout << sorted[i] << " ";
  }
  delete[] heap;
  delete[] sorted;
  return 0;
}