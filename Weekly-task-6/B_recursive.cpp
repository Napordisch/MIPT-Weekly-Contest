#include <iostream>

int32_t Partition(int32_t* arr, size_t n) {
  int32_t pivot = arr[n - 1];

  size_t i = 0;

  for (size_t j = 0; j < n - 1; j++) {
    if (arr[j] <= pivot) {
      int32_t t = arr[j];
      arr[j] = arr[i];
      arr[i] = t;
      i++;
    }
  }
  int32_t t = arr[i];
  arr[i] = arr[n - 1];
  arr[n - 1] = t;
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
  uint32_t n_all_people, m_groups, k_group_size;
  std::cin >> n_all_people >> m_groups >> k_group_size;
  auto* arr = new int32_t[n_all_people];
  for (uint32_t i = 0; i < n_all_people; i++) {
    std::cin >> arr[i];
  }
  QuickSort(arr, n_all_people);
  uint32_t min_diff;

  if (k_group_size == 1) {
    std::cout << 0;
    delete[] arr;
    return 0;
  }

int CurStartMinDiff(int32_t* arr, ) {
  uint32_t steps = 0;

}

  // for (uint32_t start = n_all_people - 1; start >= m_groups * k_group_size - 1; start--) {
  //   uint32_t max_diff = 0;
  //   uint32_t highest_i = start;
  //   uint32_t steps = 0;

  //   while (steps < m_groups) {
  //     uint32_t diff = arr[highest_i] - arr[highest_i - (k_group_size - 1)];
  //     if (diff > max_diff) {
  //       max_diff = diff;
  //     }
  //     steps++;
  //     if (steps < m_groups) {
  //       highest_i -= k_group_size;
  //     }
  //   }
  //   if (start == n_all_people - 1) {
  //     min_diff = max_diff;
  //   } else if (max_diff < min_diff) {
  //     min_diff = max_diff;
  //   }
  // }

  for (uint32_t start = 0; start <= n_all_people - m_groups * k_group_size; start++) {
    uint32_t max_diff = 0;
    uint32_t lowest_i = start;
    

    while (steps < m_groups) {
      uint32_t diff = arr[lowest_i + (k_group_size - 1)] - arr[lowest_i];
      if (diff > max_diff) {
        max_diff = diff;
      }
      steps++;
      if (steps < m_groups) {
        lowest_i += k_group_size;
      }
    }
    if (start == 0) {
      min_diff = max_diff;
    } else if (max_diff < min_diff) {
      min_diff = max_diff;
    }
  }


  std::cout << min_diff;

  delete[] arr;
  return 0;
}