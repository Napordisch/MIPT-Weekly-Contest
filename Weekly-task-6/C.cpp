#include <iostream>

int32_t Partition(int32_t* arr, size_t n, std::string* strarr) {
  int32_t pivot = arr[n - 1];

  size_t i = 0;

  for (size_t j = 0; j < n - 1; j++) {
    if (arr[j] >= pivot) {
      int32_t t = arr[j];
      arr[j] = arr[i];
      arr[i] = t;

      // name swap
      if (arr[i] != arr[j]) {
        std::cout << "swap"
                  << "\n";
        std::string str_t = strarr[j];
        strarr[j] = strarr[i];
        strarr[i] = str_t;
      }
      i++;
    }
  }
  int32_t t = arr[i];
  arr[i] = arr[n - 1];
  arr[n - 1] = t;
  // name swap
  if (arr[i] != arr[n - 1]) {
    std::cout << "swap"
              << "\n";
    std::string str_t = strarr[i];
    strarr[i] = strarr[n - 1];
    strarr[n - 1] = str_t;
  }

  return i;
}

void QuickSort(int32_t* arr, size_t n, std::string* strarr) {
  if (n <= 1) {
    return;
  }

  size_t i = Partition(arr, n, strarr);

  QuickSort(arr, i, strarr);
  QuickSort(arr + i, n - i, strarr + i);
}

int main() {
  size_t n;
  std::cin >> n;
  int32_t* grades = new int32_t[n];
  std::string* names = new std::string[n];
  for (size_t i = 0; i < n; i++) {
    std::string first_name, last_name;
    int32_t grade_1, grade_2, grade_3;

    std::cin >> first_name >> last_name >> grade_1 >> grade_2 >> grade_3;

    grades[i] = (grade_1 + grade_2 + grade_3);
    names[i] = first_name + " " + last_name;
  }
  QuickSort(grades, n, names);
  for (size_t i = 0; i < n; i++) {
    std::cout << names[i] << "\n";
  }

  delete[] names;
  delete[] grades;
  return 0;
}