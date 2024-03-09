#include <iostream>

using std::cin;
using std::cout;

int main() {
  uint16_t cities;
  cin >> cities;

  uint16_t** roads = new uint16_t*[cities];
  for (uint16_t i = 0; i < cities; i++) {
    roads[i] = new uint16_t[cities]{0};
  }

  uint16_t amount_of_roads = 0;

  for (uint16_t i = 0; i < cities; i++) {
    for (uint16_t j = 0; j < cities; j++) {
      uint16_t road;
      cin >> road;
      if (road == 1 && roads[j][i] != 1) {
        amount_of_roads++;
      }
      roads[i][j] = road;
    }
  }

  for (uint16_t i = 0; i < cities; i++) {
    for (uint16_t j = 0; j < cities; j++) {
      cout << roads[i][j] << " ";
    }
    cout << "\n";
  }
  cout << amount_of_roads << "\n";

  return 0;
  delete[] roads;
}
