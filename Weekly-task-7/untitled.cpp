#include <iostream>
#include <cmath>

void Swap(int32_t& a, int32_t& b) {
  int32_t t = a;
  a = b;
  b = t;
}


void SiftUp(int32_t* arr, size_t id) {
  while(id > 0) {
    parent_id = (id - 1) / 2;
    if (arr[parent_id] < arr[id]) {
      swap(arr[parent_id], arr[id]);
      id = parent_id;
    } else {
      break;
    }
  }
}

void SiftDown(int32_t* arr, size_t n, size_t id) {
  while (id < n) {
    int32_t left_child_id = id * 2 + 1;
    int32_t right_child_id = id * 2 + 2;
    int32_t max_id = id;
    if (left_child_id < n && arr[left_child_id] > arr[max_id]) {
      max_id = left_child_id;
    }
    if (right_child_id < n && arr[right_child_id] > arr[max_id]) {
      max_id = right_child_id;
    }
    if (id != max_id) {
      swap(arr[id], arr[max_id]);
      id = max_id;
    } else {
      break;
    }
  }
}

void ExtractMax(int32_t* arr, size_t& n) {
  swap(arr[0], arr[n - 1]);
  n--;
  int32_t max = arr[n - 1];
  SiftDown(arr, 0);
}

void GetMin(int32_t* arr, size_t n){
  size_t min_index = n - 1;
  for (size_t i = 0; i < n) {
    if (arr[i] < arr[min_index]) {
      min_index = i;
    }
  }
  return i;
}

void Resize(int32_t*& arr; size_t &n, size_t& capacity, in32_t elem) {
  int32_t* new_arr = new int32_t[2*capacity];
  for (size_t i = 0; i < capacity; i++) {
    new_arr[i] = arr[i];
  }
  delete[] arr;
  arr = new_arr;
  capacity = capacity * 2;
}

void Push(int32_t*& arr, size_t& n, size_t& capacity, int32_t elem) { //insert
  if (n >= capacity - 1) {
    resize(arr, n, elem);
  }
  arr[n] = elem;
  n++;
  SiftUp(arr, n);
}

