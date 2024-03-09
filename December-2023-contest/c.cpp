#include <iostream>

using std::cin;
using std::cout;

int binsearch(int *array, int guess, int len) {
  int l = 0;
  int r = len - 1;
  int index = -1;
  while (l < r) {
    int m = (l + r) / 2;
    if (guess < array[m]) {
      r = m - 1;
      continue;
    }
    if (guess > array[m]) {
      l = m + 1;
      continue;
    }
    index = m + 1;
    break;
  }
  if (guess == array[l]) {
    index = l + 1; 
  } else if (guess == array[r]) {
    index = r + 1;
  }
  return index;
}
 
int main() {
  int n, k;
  cin >> n;
  int *stones = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> stones[i];
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    int guess;
    cin >> guess;
    cout << binsearch(stones, guess, n) << " ";
  }
  delete[] stones;
  return 0;
}