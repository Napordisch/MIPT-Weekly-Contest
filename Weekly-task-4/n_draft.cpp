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
  uint16_t first_one_encountered = 0;
  uint16_t win = 0;
  uint16_t nerf = 0;
  uint16_t first_unchosen = 0;
  for (uint16_t i = 0; i < max_chosen; i++) {
    if (number_count[i] == 0) {
      if (first_one_encountered == 0) {
        win = i + 1;
      }
      if (first_unchosen == 0) {
        first_unchosen = i + 1;
      }
    } else if (number_count[i] == 1) {
      if (first_one_encountered == 0) {
        first_one_encountered = i + 1;
      }
      if (nerf == 0) {
        if (number_scores[i] < scores[n - 1] && number_scores[i] + i + 1 >= scores[n - 1]) {
          nerf = i + 1;
        }
      }
    }
  }

  // output
  if (win != 0) {
    std::cout << win;
  } else if (nerf != 0) {
    std::cout << nerf;
  } else if (first_unchosen != 0) {
    std::cout << first_unchosen;
  } else {
    std::cout << 1;
  }
  delete[] scores;
  delete[] chosen_numbers;
  delete[] number_count;
  delete[] number_scores;
  return 0;
}