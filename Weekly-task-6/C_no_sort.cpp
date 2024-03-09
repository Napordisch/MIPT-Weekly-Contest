#include <iostream>

void Merge(const int32_t* l, size_t l_len, const int32_t* r, size_t r_len,
           int32_t* buffer) {
  size_t l_index = 0;
  size_t r_index = 0;
  // with comparison
  while (l_index < l_len && r_index < r_len) {
    if (l[l_index] >= r[r_index]) {
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

void RecursiveMergeSort(int32_t* arr, size_t n, int32_t* buffer) {
  if (n <= 1) {
    return;
  }
  size_t middle = n / 2;
  RecursiveMergeSort(arr, middle, buffer);
  RecursiveMergeSort(arr + middle, n - middle, buffer);
  Merge(arr, middle, arr + middle, n - middle, buffer);
  for (size_t i = 0; i < n; i++) {
    arr[i] = buffer[i];
  }
}

void MergeSort(int32_t* arr, size_t n) {
  int32_t* buffer = new int32_t[n];
  RecursiveMergeSort(arr, n, buffer);
  delete[] buffer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  size_t n;
  std::cin >> n;
  int32_t* grades = new int32_t[n];
  int32_t* grades_copy = new int32_t[n];
  std::string* names = new std::string[n];

  size_t grades_copy_i = 0;
  for (size_t i = 0; i < n; i++) {
    std::string first_name, last_name;
    int32_t grade_1, grade_2, grade_3;
    std::cin >> first_name >> last_name >> grade_1 >> grade_2 >> grade_3;
    int32_t sum = grade_1 + grade_2 + grade_3;
    grades[i] = sum;
    if (sum != grades_copy[grades_copy_i]) {
      grades_copy[grades_copy_i] = sum;
      grades_copy_i++;
    }
    names[i] = first_name + " " + last_name;
  }

  MergeSort(grades_copy, grades_copy_i);

  size_t displayed = 0;
  for (size_t i = 0; i < grades_copy_i; i++) {
    for (size_t j = 0; j < n; j++) {
      if (grades[j] == grades_copy[i]) {
        std::cout << names[j] << "\n";
        displayed++;
      }
    }
    if (displayed >= 3) {
      break;
    }
  }

  delete[] names;
  delete[] grades_copy;
  delete[] grades;
  return 0;
}