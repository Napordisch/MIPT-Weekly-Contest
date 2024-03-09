#include <iostream>

using std::cin;
using std::cout;

enum color : int16_t { red = 1, blud = 2, green = 3 };

enum bridge : int16_t { no = 0, bad = -1, good = 1 };

int main() {
  uint16_t hills_amount = 0;
  cin >> hills_amount;

  int16_t **bridges = new int16_t *[hills_amount];

  for (uint16_t i = 0; i < hills_amount; i++) {
    bridges[i] = new int16_t[hills_amount];

    for (uint16_t j = 0; j < hills_amount; j++) {
      cin >> bridges[i][j];
    }
  }

  int16_t *colors = new int16_t[hills_amount];

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

  cout << "Table with bad bridges"
    << "\n";
  for (uint16_t i = 0; i < hills_amount; i++) {
    for (uint16_t j = 0; j < hills_amount; j++) {
      cout << bridges[i][j] << " ";
    }
    cout << "\n";
  }

  cout << bad_bridges << "\n";

  for (uint16_t i = 0; i < hills_amount; i++) {
    delete[] bridges[i];
  }
  delete[] bridges;
  delete[] colors;
}
