#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  size_t n;
  std::cin >> n;
  std::string* first_names = new std::string[n];
  std::string* last_names = new std::string[n];
  int32_t* grades = new int32_t[n];

  for (size_t i = 0; i < n; i++) {
    int32_t grade_1, grade_2, grade_3;
    std::cin >> first_names[i] >> last_names[i] >> grade_1 >> grade_2 >>
        grade_3;
    grades[i] = grade_1 + grade_2 + grade_3;
  }

  std::string top_first_names[3];
  std::string top_last_names[3];

  int32_t* top_grades = new int32_t[3];

  for (size_t i = 0; i < n; i++) {
    int32_t grade = grades[i];

    for (int j = 0; j < 3; j++) {
      if (grade > top_grades[j] ||
          (grade == top_grades[j] &&
           (j == 2 || last_names[i] == top_last_names[j]))) {
        for (int k = 2; k > j; k--) {
          top_grades[k] = top_grades[k - 1];
          top_first_names[k] = top_first_names[k - 1];
          top_last_names[k] = top_last_names[k - 1];
        }

        top_grades[j] = grade;
        top_first_names[j] = first_names[i];
        top_last_names[j] = last_names[i];
        break;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    std::cout << top_first_names[i] << " " << top_last_names[i] << "\n";
  }

  delete[] grades;
  delete[] first_names;
  delete[] last_names;
  delete[] top_grades;
  return 0;
}