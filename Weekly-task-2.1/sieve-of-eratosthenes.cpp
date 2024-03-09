#include <iostream>

uint64_t SieveOfEratosthenes(uint64_t num) {
  bool *primes = new bool[num + 1];

  for (uint64_t i = 0; i < num + 1; i++) {
    primes[i] = true;
  }

  uint64_t p = 2;
  while (p * p <= num) {
    if (primes[p] == true) {
      for (uint64_t i = p * p; i < num + 1; i += p) {
        primes[i] = false;
      }
    }
    p += 1;
  }
  uint64_t i = num;
  bool maybe_prime = primes[i];
  while (maybe_prime == false) {
    i--;
    maybe_prime = primes[i];
  }
  return i;
}

int main () {
  std::cout << SieveOfEratosthenes(10000000) << "\n";
}