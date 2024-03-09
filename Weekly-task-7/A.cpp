#include <iostream>


void Swap(int32_t& a, int32_t& b) {
  int32_t t = a;
  a = b;
  b = t;
}

void Swap(size_t& a, size_t& b) {
  size_t t = a;
  a = b;
  b = t;
}


void DisplayHeap(int32_t* heap, size_t size) {
  std::cout << "Heap: " << "\n";
  size_t i = 0;
  size_t line_size = 1;
  while (i < size) {
    for (size_t j = 0; j < line_size; j++) {
      if (i < size) {
        std::cout << heap[i] << "\t";
        i++;
      } else {
        break;
      }
    }
    std::cout << "\n";
    line_size = line_size * 2;
  }
}

// for heaps with indexes
void DisplayHeap(size_t* heap, size_t size) {
  std::cout << "Heap: " << "\n";
  size_t i = 0;
  size_t line_size = 1;
  while (i < size) {
    for (size_t j = 0; j < line_size; j++) {
      if (i < size) {
        std::cout << heap[i] << "\t";
        i++;
      } else {
        break;
      }
    }
    std::cout << "\n";
    line_size = line_size * 2;
  }
}

void SiftUp(int32_t* heap, size_t id, size_t* insert_indexes, size_t* insert_indexes_heap) {
  while(id > 0) {
    size_t parent_id = (id - 1) / 2;
    if (heap[parent_id] < heap[id]) {
      // std::cout << "sift up\n";
      Swap(heap[parent_id], heap[id]);
      Swap(insert_indexes_heap[parent_id], insert_indexes_heap[id]);
      insert_indexes[insert_indexes_heap[parent_id]] = parent_id;
      insert_indexes[insert_indexes_heap[id]] = id;
      // Swap(insert_indexes[insert_indexes_heap[parent_id]], insert_indexes[insert_indexes_heap[id]])
      id = parent_id;
    } else {
      break;
    }
  }
}

void SiftDown(int32_t* heap, size_t size, size_t id, size_t* insert_indexes, size_t* insert_indexes_heap) {
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
      Swap(insert_indexes_heap[id], insert_indexes_heap[max_id]);
      insert_indexes[insert_indexes_heap[max_id]] = max_id;
      insert_indexes[insert_indexes_heap[id]] = id;
      id = max_id;
    } else {
      break;
    }
  }
}

void Delete(int32_t* heap, size_t& size, size_t id, size_t* insert_indexes, size_t* insert_indexes_heap) {
  Swap(heap[id], heap[size - 1]);
  Swap(insert_indexes_heap[id], insert_indexes_heap[size - 1]);

  insert_indexes[insert_indexes_heap[id]] = id;
  insert_indexes[insert_indexes_heap[size - 1]] = size - 1;
  insert_indexes[insert_indexes_heap[size - 1]] = -1;

  size--;
  SiftDown(heap, size, id, insert_indexes, insert_indexes_heap);
}

void Change(int32_t* heap, size_t& size, size_t id, size_t* insert_indexes, size_t* insert_indexes_heap, int32_t new_value) {
  int32_t old_value = heap[id];
  heap[id] = new_value;
  if (new_value > old_value) {
    SiftUp(heap, id, insert_indexes, insert_indexes_heap);
  } else if (new_value < old_value) {
    SiftDown(heap, size, id, insert_indexes, insert_indexes_heap);
  }
}

void Resize(int32_t*& heap, size_t& capacity, size_t*& insert_indexes, size_t*& insert_indexes_heap) {
  auto* new_heap = new int32_t[2*capacity];
  auto* new_indexes = new size_t[2*capacity];
  auto* new_insert_indexes_heap = new size_t[2*capacity];
  for (size_t i = 0; i < capacity; i++) {
    new_heap[i] = heap[i];
    new_indexes[i] = insert_indexes[i];
    new_insert_indexes_heap[i] = insert_indexes_heap[i];
  }  
  delete[] heap;
  delete[] insert_indexes;
  delete[] insert_indexes_heap;
  heap = new_heap;
  insert_indexes = new_indexes;
  insert_indexes_heap = new_insert_indexes_heap;
  capacity = capacity * 2;
}

void Insert(int32_t*& heap, size_t& size, size_t& capacity, size_t*& insert_indexes, size_t& x, size_t*& insert_indexes_heap) {
  int32_t elem;
  std::cin >> elem;
  if (size >= capacity - 1) {
    Resize(heap, capacity, insert_indexes, insert_indexes_heap);
  }
  heap[size] = elem;
  insert_indexes_heap[size] = x;
  // std::cout << "x: " << x << "\t" << "size: " << size << "\t" << "insert_indexes_heap[size]: " << insert_indexes_heap[size]<< "\t" << "insert_indexes_heap[0]: " << insert_indexes_heap[0] << "\n";
  insert_indexes[insert_indexes_heap[size]] = size;
  SiftUp(heap, size, insert_indexes, insert_indexes_heap);
  size++;
  x++;
}

size_t MinIndex(int32_t* heap, size_t size){
  size_t min_index = size - 1;
  for (size_t i = 0; i < size; i++) {
    if (heap[i] < heap[min_index] && heap[i] != 0) {
      min_index = i;
    }
  }
  return min_index;
}



int main() {
  using std::string;
  using std::cin;
  using std::cout;
  size_t m;
  cin >> m;
  size_t size = 0;
  size_t capacity = size + 1;
  auto* heap = new int32_t[capacity];
  auto* insert_indexes = new size_t[capacity];
  auto* insert_indexes_heap = new size_t[capacity];
  size_t x = 0;
  for (size_t i = 0; i < m; i++) {
    // cout << "\n" << "\n";
    // cout << i + 1;
    // cout << "\n" << "Insert indexes ";
    // DisplayHeap(insert_indexes_heap, size);
    // DisplayHeap(heap, size);
    // cout << "Insert indexes: ";
    // for (size_t i = 0; i < x; i++) {
    //   cout << insert_indexes[i] << " ";
    // }
    // cout << "\n";
    // std::cout << "insert_indexes_heap[0]" << insert_indexes_heap[0] << "\n";

    string command;
    cin >> command;

    // insert
    if (command == "insert") {
      Insert(heap, size, capacity, insert_indexes, x, insert_indexes_heap);
      cout << "ok" << "\n";
      continue;
    }

    // get_min
    if (command == "get_min") {
      cout << heap[MinIndex(heap, size)] << "\n";
      continue;
    }

    // delete
    if (command == "delete") {
      size_t in_order;
      cin >> in_order;
      size_t id = insert_indexes[in_order - 1];
      if (id < size) {
        Delete(heap, size, id, insert_indexes, insert_indexes_heap);
        cout << "ok" << "\n";
        continue;
      }
      cout << "error" << "\n";
      continue;
    }

    // size
    if (command == "size") {
      cout << size << "\n";
      continue;
    }

    // extract_min
    if (command == "extract_min") {
      if (size > 0) {
        size_t min_index = MinIndex(heap, size);
        cout << heap[min_index] << "\n";
        Delete(heap, size, min_index, insert_indexes, insert_indexes_heap);
        continue;
      }
      cout << "error" << "\n";
    }

    // change
    if (command == "change") {
      size_t in_order;
      int32_t n;
      cin >> in_order >> n;
      size_t id = insert_indexes[in_order - 1];
      if (id < size) {
        Change(heap, size, id, insert_indexes, insert_indexes_heap, n);
        cout << "ok" << "\n";
        continue;
      }
      cout << "error" << "\n";
      continue;
    }

    // clear
    if (command == "clear") {
      while (size > 0) {
        Delete(heap, size, size - 1, insert_indexes, insert_indexes_heap);
      }
      cout << "ok" << "\n";
      continue;
    }  
  }
  delete[] heap;
  delete[] insert_indexes;
  delete[] insert_indexes_heap;
}