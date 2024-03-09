#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  size_t n;
  std::cin >> n;
  std::string first_names[n];
  std::string last_names[n];
  int math_scores[n];
  int physics_scores[n];
  int informatics_scores[n];

  for (size_t i = 0; i < n; i++) {
    std::cin >> first_names[i] >> last_names[i] >> math_scores[i] >> physics_scores[i] >> informatics_scores[i];
  }

  // Инициализируем массивы для хранения топ-3 учеников
  std::string top_first_names[3];
  std::string top_last_names[3];
  double top_avg_scores[3] = {0.0, 0.0, 0.0};

  // Вычисляем средние баллы и определяем топ-3
  for (size_t i = 0; i < n; i++) {
    double avg_score = (math_scores[i] + physics_scores[i] + informatics_scores[i]) / 3.0;

    for (int j = 0; j < 3; j++) {
      if (avg_score > top_avg_scores[j] || (avg_score == top_avg_scores[j] && (j == 2 || last_names[i] == top_last_names[j]))) {
        // Сдвигаем текущих топ-3 учеников вниз
        for (int k = 2; k > j; k--) {
          top_avg_scores[k] = top_avg_scores[k - 1];
          top_first_names[k] = top_first_names[k - 1];
          top_last_names[k] = top_last_names[k - 1];
        }

        // Заменяем ученика в топ-3
        top_avg_scores[j] = avg_score;
        top_first_names[j] = first_names[i];
        top_last_names[j] = last_names[i];
        break;
      }
    }
  }

  // Выводим топ-3 учеников
  for (int i = 0; i < 3; i++) {
    std::cout << top_first_names[i] << " " << top_last_names[i] << "\n";
  }

  return 0;
}
