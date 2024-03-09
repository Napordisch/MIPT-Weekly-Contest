#include <iostream>
#include <stdint.h>

using std::cin;
using std::cout;

int main() {
  uint16_t hills_amount = 0;
  cin >> hills_amount;

  auto **bridges = new int16_t *[hills_amount];

  for (uint16_t i = 0; i < hills_amount; i++) {
    bridges[i] = new int16_t[hills_amount];

    for (uint16_t j = 0; j < hills_amount; j++) {
      cin >> bridges[i][j];
    }
  }

  auto *colors = new int16_t[hills_amount];

  for (uint16_t i = 0; i < hills_amount; i++) {
    cin >> colors[i];
  }

  uint16_t bad_bridges = 0;
  for (uint16_t i = 0; i < hills_amount; i++) {
    for (uint16_t j = 0; j < hills_amount; j++) {
      if (bridges[i][j] == 1 && colors[i] != colors[j]) {
        bridges[i][j] = -1;
        bridges[j][i] = -1;
        bad_bridges++;
      }
    }
  }

  cout << bad_bridges << "\n";

  for (uint16_t i = 0; i < hills_amount; i++) {
    delete[] bridges[i];
  }
  delete[] bridges;
  delete[] colors;
}
