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
  // int32_t *karray = new int32_t[k];
  for (int32_t i = 0; i < k; i++){
    int32_t elem;
    std::cin >> elem;
    int32_t l = 0;
    int32_t r = n - 1;
    bool found = false;
    std::cout << "elem:" << elem << "\n";
    while (l <= r) {
      int32_t m = (l + r) / 2;
      std::cout << "Before:" << "  ";
      std::cout << "L:" << l << " " << "M:" << m << " " << "M number: " << narray[m] << " " << "R:" << r << "\n";
      if (narray[m] > elem) {
        r = m - 1;
      } else if (narray[m] < elem) {
        l = m + 1;
      } else {
        found = true;
        break;
      }
      std::cout << "After:" << "   ";
      std::cout << "L:" << l << " " << "M:" << m << " " << "R:" << r << "\n";
    }
    if (found || narray[l] == elem || narray[r] == elem){
      std::cout << "YES" << "\n" << "\n";
    } else {
      std::cout << "NO" << "\n" << "\n";
    }
  }
}