#include <iostream>
// comment
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  size_t n;
  std::cin >> n;
  int32_t* grades = new int32_t[n];
  int32_t* top_3_grades = new int32_t[3];
  uint32_t* top_3_count = new uint32_t[3];
  for (int32_t i = 0; i < 3; i++) {
    top_3_grades[i] = 0;
    top_3_count[i] = 0;
  }
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

    for (size_t j = 0; j < 3; j++) {
      if (sum > top_3_grades[j]) {
        for (size_t k = 2; k > j; k--) {
          top_3_grades[k] = top_3_grades[k - 1];
          top_3_count[k] = top_3_count[k - 1];
        }
        top_3_grades[j] = sum;
        break;
      } 
      if (sum == top_3_grades[j]) {
        top_3_count[j]++;
      }
    }
  }

  uint32_t firsts = top_3_count[0];
  uint32_t seconds = top_3_count[1];
  uint32_t thirds = top_3_count[2];
  // for (size_t i = 0; i < n; i++) {
  //   int32_t grade = grades[i];
  //   if (grade > top_3_grades[0]) {
  //     top_3_grades[2] = top_3_grades[1];
  //     top_3_grades[1] = top_3_grades[0];
  //     top_3_grades[0] = grade;
  //     thirds = seconds;
  //     seconds = firsts;
  //     firsts = 1;
  //   } else if (grade > top_3_grades[1] && grade != top_3_grades[0]) {
  //     top_3_grades[2] = top_3_grades[1];
  //     top_3_grades[1] = grade;
  //     thirds = seconds;
  //     seconds = 1;
  //   } else if (grade > top_3_grades[2]) {
  //     top_3_grades[2] = grade;
  //     thirds = 1;
  //   } else if (grade == top_3_grades[0]) {
  //     firsts++;
  //   } else if (grade == top_3_grades[1]) {
  //     seconds++;
  //   } else if (grade == top_3_grades[2]) {
  //     thirds++;
  //   }
  // }

  if (firsts >= 3) {
    for (size_t i = 0; i < n; i++) {
      if (grades[i] == top_3_grades[0]) {
        std::cout << first_names[i] << " " << last_names[i] << "\n";
      }
    }
  } else if (firsts + seconds >= 3) {
    for (size_t i = 0; i < n; i++) {
      if (grades[i] == top_3_grades[0] || grades[i] == top_3_grades[1]) {
        std::cout << first_names[i] << " " << last_names[i] << "\n";
      }
    }
  } else {
    for (size_t i = 0; i < n; i++) {
      if (grades[i] == top_3_grades[0] || grades[i] == top_3_grades[1] ||
          grades[i] == top_3_grades[2]) {
        std::cout << first_names[i] << " " << last_names[i] << "\n";
      }
    }
  }

  delete[] first_names;
  delete[] last_names;
  delete[] top_3_grades;
  delete[] grades;
  return 0;
}