#include <iostream>

void BubbleSort(uint32_t *array, size_t array_size) {
  for (size_t i = 1; i < array_size; i++) {
    for (size_t j = 0; j < array_size - i; j++) {
      if (array[j] > array[j + 1]) {
        int32_t t = array[j];
        array[j] = array[j + 1];
        array[j + 1] = t;
      }
    }
  }
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  uint32_t *capacity = new uint32_t[n * m];
  for (size_t i = 0; i < n * m; i++) {
    std::cin >> capacity[i];
  }

  size_t k;
  std::cin >> k;
  uint32_t *mesklinites = new uint32_t[k];
  for (size_t i = 0; i < k; i++) {
    std::cin >> mesklinites[i];
  }

  BubbleSort(capacity, n * m);
  BubbleSort(mesklinites, k);

  uint32_t max_expedition_crew = 0;
  for (size_t i = 0; i < k; i++) {
    for (size_t j = 0; j < n * m; j++) {
      if (mesklinites[i] <= capacity[j]) {
        max_expedition_crew++;
        capacity[j] = 0;
        break;
      }
    }
  }

  std::cout << max_expedition_crew;

  delete[] capacity;
  delete[] mesklinites;
  return 0;
}