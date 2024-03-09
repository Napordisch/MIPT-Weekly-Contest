#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  size_t n;
  std::cin >> n;
  int32_t* grades = new int32_t[n];
  int32_t* top_3_grades = new int32_t[3];
  for (int32_t i = 0; i < 3; i++) {
    top_3_grades[i] = 0;
  }
  std::string* names = new std::string[n];

  for (size_t i = 0; i < n; i++) {
    std::string first_name, last_name;
    int32_t grade_1, grade_2, grade_3;
    std::cin >> first_name >> last_name >> grade_1 >> grade_2 >> grade_3;
    int32_t sum = grade_1 + grade_2 + grade_3;
    if (sum > top_3_grades[0]) {
      top_3_grades[2] = top_3_grades[1];
      top_3_grades[1] = top_3_grades[0];
      top_3_grades[0] = sum;
    } else if (sum > top_3_grades[1] && sum != top_3_grades[0]) {
      top_3_grades[2] = top_3_grades[1];
      top_3_grades[1] = sum;
    } else if (sum > top_3_grades[2]) {
      top_3_grades[2] = sum;
    }
    grades[i] = sum;

    names[i] = first_name + " " + last_name;
  }

  size_t displayed = 0;
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < n; j++) {
      if (grades[j] == top_3_grades[i]) {
        std::cout << names[j] << "\n";
        displayed++;
      }
    }
    if (displayed >= 3) {
      break;
    }
  }

  delete[] names;
  delete[] top_3_grades;
  delete[] grades;
  return 0;
}