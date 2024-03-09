#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(0);
  int32_t n, k;
  std::cin >> n >> k;
  int32_t *narray = new int32_t[n];
  for (int32_t i = 0; i < n; i++) {
    int32_t number;
    std::cin >> number;
    narray[i] = number;
  }
  for (int32_t i = 0; i < k; i++){
    int32_t elem;
    std::cin >> elem;
    int32_t l = 0;
    int32_t r = n;
    while (l < r - 1) {
      int32_t m = (l + r) / 2;
      if (elem >= narray[m]) {
        l = m;
      } else {
        r = m;
      }
    }
    if (narray[l] == elem){
      std::cout << "YES" << "\n";
    } else {
      std::cout << "NO" << "\n";
    }
  }
  delete[] narray;
}