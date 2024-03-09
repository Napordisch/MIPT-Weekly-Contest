#include <iostream>

int main() {
  // input
  uint16_t n;
  std::cin >> n;
  uint16_t* scores = new uint16_t[n];              // scores of players (n-1 – Petya's score)
  uint16_t* chosen_numbers = new uint16_t[n - 1];  // chosen by others
  uint16_t* number_count = new uint16_t[100];      // how many times the number appears
  uint16_t* number_scores = new uint16_t[100];     // how many points a number owner has
  for (uint16_t i = 0; i < 100; i++) {
    number_count[i] = 0;
    number_scores[i] = 0;
  }

  for (uint16_t i = 0; i < n; i++) {
    std::cin >> scores[i];
  }
  uint16_t max_chosen = 0;
  for (uint16_t i = 0; i < n - 1; i++) {
    std::cin >> chosen_numbers[i];
    if (chosen_numbers[i] > max_chosen) {
      max_chosen = chosen_numbers[i];
    }
    number_count[chosen_numbers[i] - 1]++;
    number_scores[chosen_numbers[i] - 1] = scores[i];
  }
  bool one_encountered = false;
  uint16_t chosen_by_p = 1;
  for (uint16_t i = 0; i < max_chosen; i++) {
    if (number_count[i] == 0) {
      if (!one_encountered) {
        chosen_by_p = i + 1;
      }
      chosen_by_p = (chosen_by_p == 1) * (i + 1) + chosen_by_p;
    }
    if (number_count[i] == 1) {
      one_encountered = true;
      if (number_scores[i] < scores[n - 1] && number_scores[i] + i + 1 > scores[n - 1]) {
        chosen_by_p = i + 1;
        break;
      }
    }
  }
  std::cout << chosen_by_p;
  delete[] scores;
  delete[] chosen_numbers;
  delete[] number_count;
  delete[] number_scores;
  return 0;
}