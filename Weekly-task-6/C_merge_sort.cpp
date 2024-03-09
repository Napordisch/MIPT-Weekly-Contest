#include <iostream>

void Merge(const int32_t* l, size_t l_len, const int32_t* r, size_t r_len,
           int32_t* buffer, std::string* l_strarr, std::string* r_strarr,
           std::string* str_buffer) {
  size_t l_index = 0;
  size_t r_index = 0;
  // with comparison
  while (l_index < l_len && r_index < r_len) {
    if (l[l_index] >= r[r_index]) {
      buffer[l_index + r_index] = l[l_index];
      str_buffer[l_index + r_index] = l_strarr[l_index];
      l_index++;
    } else {
      buffer[l_index + r_index] = r[r_index];
      str_buffer[l_index + r_index] = r_strarr[r_index];
      r_index++;
    }
  }
  // if r_len > l_len or l_len > r_len
  while (l_index < l_len) {
    buffer[l_index + r_index] = l[l_index];
    str_buffer[l_index + r_index] = l_strarr[l_index];
    l_index++;
  }
  while (r_index < r_len) {
    buffer[l_index + r_index] = r[r_index];
    str_buffer[l_index + r_index] = r_strarr[r_index];
    r_index++;
  }
}

void RecursiveMergeSort(int32_t* arr, size_t n, int32_t* buffer,
                        std::string* strarr, std::string* str_buffer) {
  if (n <= 1) {
    return;
  }
  size_t middle = n / 2;
  RecursiveMergeSort(arr, middle, buffer, strarr, str_buffer);
  RecursiveMergeSort(arr + middle, n - middle, buffer, strarr + middle,
                     str_buffer);
  Merge(arr, middle, arr + middle, n - middle, buffer, strarr, strarr + middle,
        str_buffer);
  for (size_t i = 0; i < n; i++) {
    arr[i] = buffer[i];
  }
  for (size_t i = 0; i < n; i++) {
    strarr[i] = str_buffer[i];
  }
}

void MergeSort(int32_t* arr, size_t n, std::string* strarr) {
  int32_t* buffer = new int32_t[n];
  std::string* str_buffer = new std::string[n];
  RecursiveMergeSort(arr, n, buffer, strarr, str_buffer);
  delete[] str_buffer;
  delete[] buffer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  size_t n;
  std::cin >> n;
  int32_t* grades = new int32_t[n];
  std::string* names = new std::string[n];
  for (size_t i = 0; i < n; i++) {
    std::string first_name, last_name;
    int32_t grade_1, grade_2, grade_3;

    std::cin >> first_name >> last_name >> grade_1 >> grade_2 >> grade_3;

    grades[i] = (grade_1 + grade_2 + grade_3);
    names[i] = first_name + " " + last_name;k  
  }
  MergeSort(grades, n, names);
  for (size_t i = 0; i < n; i++) {
    std::cout << names[i] << "\n";
  }

  delete[] names;
  delete[] grades;
  return 0;
}