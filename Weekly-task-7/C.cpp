#include <iostream>

void Swap(int32_t& a, int32_t& b) {
  int32_t t = a;
  a = b;
  b = t;
}

int32_t SiftUp(int32_t* heap, int32_t id) {
  while (id > 0) {
    int32_t parent_id = (id - 1) / 2;
    if (heap[parent_id] < heap[id]) {
      Swap(heap[parent_id], heap[id]);
      id = parent_id;
    } else {
      break;
    }
  }
  return id;
}

int32_t SiftDown(int32_t* heap, int32_t size, int32_t id) {
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
  return id;
}

void ExtractMax(int32_t* heap, int32_t& size) {
  // heap[0] is max
  Swap(heap[0], heap[size - 1]);
  int32_t max = heap[size - 1];
  size--;
  if (size != 0) {
    std::cout << SiftDown(heap, size, 0) + 1 << " " << max << "\n";
  } else {
    std::cout << 0 << " " << max << "\n";
  }
}

void Push(int32_t*& heap, int32_t& size) {
  std::cin >> heap[size];
  std::cout << SiftUp(heap, size) + 1 << "\n";
  size++;
}

int main() {
  int32_t n, m;
  std::cin >> n >> m;
  int32_t size = 0;
  auto* heap = new int32_t[n];
  for (int32_t i = 0; i < m; i++) {
    int32_t command;
    std::cin >> command;
    if (command == 1) {
      if (size == 0) {
        std::cout << "-1"
                  << "\n";
        continue;
      }
      ExtractMax(heap, size);
      continue;
    }
    if (command == 2) {
      if (size == n) {
        int32_t fake_num;
        std::cin >> fake_num;
        std::cout << "-1"
                  << "\n";
        continue;
      }
      Push(heap, size);
      continue;
    }
  }
  for (int32_t i = 0; i < size; i++) {
    std::cout << heap[i] << " ";
  }
  delete[] heap;
  return 0;
}