#include <iostream>

bool NecklaceSort(int32_t *necklace, int32_t necklace_length, int32_t *necklace_swaps, int32_t *necklace_swaps_amount) {
  bool sorted = false;
  if (necklace_length == 2) {
    return true;
  }
  int32_t a = necklace_length - 1;
  int32_t b = necklace_length - 2;
  int32_t swaps_counter = 0; // Счетчик перестановок

  while (!sorted) {
    if ((necklace[a] - necklace[b]) > 1 || (necklace[b] - necklace[a]) > 1) {
      int32_t t = necklace[a];
      necklace[a] = necklace[b];
      necklace[b] = t;

      necklace_swaps[(*necklace_swaps_amount) * 2] = necklace[a];
      necklace_swaps[(*necklace_swaps_amount) * 2 + 1] = necklace[b];
      (*necklace_swaps_amount)++;

      swaps_counter++; // Увеличиваем счетчик перестановок

      if (swaps_counter >= 50000) {
        return false; // Если сделано 50 000 перестановок, завершаем выполнение
      }
    }

    if (b > 0) {
      a = b;
      b--;
    } else if (b == 0) {
      a = b;
      b = necklace_length - 1;
    }

    int32_t wrongs = 0;
    for (int32_t i = 1; i < necklace_length; i++) {
      if (necklace[i - 1] > necklace[i]) {
        wrongs++;
      }
    }
    if (necklace[necklace_length - 1] > necklace[0]) {
      wrongs++;
    }

    if (wrongs < 2) {
      sorted = true;
    }
  }
  return true;
}

int main() {
  int32_t n;
  std::cin >> n;
  int32_t necklace_swaps_amount = 0;
  int32_t *necklace = new int32_t[n];

  for (int32_t i = 0; i < n; i++) {
    std::cin >> necklace[i];
  }

  int32_t *necklace_swaps = new int32_t[50000 * 2];
  bool sorted = NecklaceSort(necklace, n, necklace_swaps, &necklace_swaps_amount);
  if (sorted) {
    for (int32_t i = 0; i < necklace_swaps_amount; i++) {
      std::cout << necklace_swaps[i * 2] << " " << necklace_swaps[i * 2 + 1] << "\n";
    }
    std::cout << 0;
  } else {
    std::cout << -1;
  }

  delete[] necklace;
  delete[] necklace_swaps;
  return 0;
}
