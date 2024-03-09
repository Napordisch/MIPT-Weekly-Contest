#include <iostream>

void Swap(int32_t& a, int32_t& b) {
  int32_t t = a;
  a = b;
  b = t;
}

void SiftUp(int32_t* heap, int32_t id) {
  while (id > 0) {
    int32_t parent_id = (id - 1) / 2;
    if (heap[parent_id] < heap[id]) {
      Swap(heap[parent_id], heap[id]);
      id = parent_id;
    } else {
      break;
    }
  }
}

void SiftDown(int32_t* heap, int32_t size, int32_t id) {
  while (id < size) {
    int32_t left_child_id = id * 2 + 1;
    int32_t right_child_id = id * 2 + 2;
    int32_t max_id = id;
    if (left_child_id < size && heap[left_child_id] > heap[max_id]) {
      max_id = left_child_id;
    }
    if (right_child_id < size && heap[right_child_id] > heap[max_id]) {
      max_id = right_child_id;
    }
    if (id != max_id) {
      Swap(heap[id], heap[max_id]);
      id = max_id;
    } else {
      break;
    }
  }
}

int32_t ExtractMax(int32_t* heap, int32_t& size) {
  // heap[0] is max
  Swap(heap[0], heap[size - 1]);
  int32_t max = heap[size - 1];
  size--;
  SiftDown(heap, size, 0);
  return max;
}

void Resize(int*& heap, int32_t& capacity, int32_t size) {
  auto* new_heap = new int32_t[2 * capacity];
  for (int32_t i = 0; i < size; i++) {
    new_heap[i] = heap[i];
  }
  delete[] heap;
  heap = new_heap;
  capacity = capacity * 2;
}

void Push(int32_t*& heap, int32_t& size, int32_t& capacity, int32_t elem) {
  if (size >= capacity) {
    Resize(heap, capacity, size);
  }
  heap[size] = elem;
  SiftUp(heap, size);
  size++;
}

int main() {
  int32_t n;
  std::cin >> n;
  int32_t size = n;
  auto* heap = new int32_t[size];
  int32_t capacity = size;
  for (int32_t i = 0; i < n; i++) {
    int32_t input;
    std::cin >> input;
    Push(heap, size, capacity, input);
  }

  auto* sorted = new int32_t[n];
  for (int32_t i = n - 1; i >= 0; i--) {
    sorted[i] = ExtractMax(heap, size);
  }
  for (int32_t i = 0; i < n; i++) {
    std::cout << sorted[i] << " ";
  }
  delete[] heap;
  delete[] sorted;
  return 0;
}