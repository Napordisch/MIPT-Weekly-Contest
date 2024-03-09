#include <iostream>

void InsertionSort(uint32_t *arr, size_t arr_size) {
  for (size_t i = 0; i < arr_size - 1; i++) {
    size_t j = i + 1;
    while (j > 0 && arr[j - 1] < arr[j]) {
      uint32_t t = arr[j - 1];
      arr[j - 1] = arr[j];
      arr[j] = t;
      j = j - 1;
    }
  }
}

int main() {
  size_t n;
  std::cin >> n;
  uint32_t *prices = new uint32_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> prices[i];
  }
  uint32_t required_money = 0;
  InsertionSort(prices, n);
  for (size_t i = 0; i < n; i += 3) {
    if (i < n - 1) {
      required_money += (prices[i] + prices[i + 1]);

    } else {
      required_money += prices[i];
    }
  }

  std::cout << required_money;

  delete[] prices;
  return 0;
}