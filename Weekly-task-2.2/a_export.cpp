#include <iostream>

using std::cin;
using std::cout;

int main() {
  uint16_t cities;
  cin >> cities;

  auto** roads = new uint16_t*[cities];
  for (uint16_t i = 0; i < cities; i++) {
    roads[i] = new uint16_t[cities]{0};
  }

  uint16_t amount_of_roads = 0;

  for (uint16_t i = 0; i < cities; i++) {
    for (uint16_t j = 0; j < cities; j++) {
      uint16_t road;
      cin >> road;
      roads[i][j] = road;
      if (road == 1 && roads[j][i] != 1) {
        amount_of_roads++;
      }
    }
  }

  cout << amount_of_roads << "\n";

  for (uint16_t i = 0; i < cities; i++) {
    delete[] roads[i];
  }
  delete[] roads;
  return 0;
}
