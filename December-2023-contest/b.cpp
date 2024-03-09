#include <iostream>
using std::cin;
int fib(int n, int *fibs) {
  fibs[0] = 1;
  fibs[1] = 1;
  for (int i = 2; i < n; i++) {
    fibs[i] = (fibs[i - 1] + fibs [i - 2]) % 10;
  }
  return fibs[n - 1];
}

int main() {
  int n;
  std::cin >> n;
  int *fibs = new int[n];
  std::cout << fib(n, fibs);
  return 0;
}