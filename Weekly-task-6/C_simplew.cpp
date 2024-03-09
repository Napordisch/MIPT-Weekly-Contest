#include <iostream>

int main() {
  size_t n;
  std::cin >> n;
  int32_t* grades = new int32_t[n];
  int32_t top1 = 0;
  int32_t top2 = 0;
  int32_t top3 = 0;
  std::string* first_names = new std::string[n];
  std::string* last_names = new std::string[n];

  for (size_t i = 0; i < n; i++) {
    std::string first_name, last_name;
    int32_t grade_1, grade_2, grade_3;
    std::cin >> first_name >> last_name >> grade_1 >> grade_2 >> grade_3;
    int32_t sum = grade_1 + grade_2 + grade_3;
    grades[i] = sum;
    first_names[i] = first_name;
    last_names[i] = last_name;
    if (sum > top1) {
      top3 = top2;
      top2 = top1;
      top1 = sum;
    } else if (sum > top2) {
      top3 = top2;
      top2 = sum;
    } else if (sum > top3) {
      top3 = sum;
    }
  }

  for (uint32_t i = 0; i < n; i++) {
    if (grades[i] >= top3) {
      std::cout << first_names[i] << " " << last_names[i] << "\n";
    }
  }

  delete[] first_names;
  delete[] last_names;
  delete[] grades;
  return 0;
}