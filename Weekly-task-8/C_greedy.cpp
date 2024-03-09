#include <iostream>

struct Queuer {
  uint32_t a;
  uint32_t b;
  uint32_t c;
};

int main() {
  uint32_t n;
  std::cin >> n;
  auto* people = new Queuer[n];
  uint32_t* sums = new uint32_t[n];
  for (uint32_t i = 0; i < n; i++) {
    std::cin >> people[i].a >> people[i].b >> people[i].c;
  }

  for (uint32_t i = 0; i < n; i++) {
    uint32_t first = i > 0 ? people[i].a + sums[i - 1] : people[i].a;
    sums[i] = first;
    if (i > 0) {
      uint32_t second = i > 1 ? people[i - 1].b + sums[i - 2] : people[i - 1].b;
      if (second < sums[i]) {
        sums[i] = second;
      }
    }
    if (i > 1) {
      uint32_t third = i > 2 ? people[i - 2].c + sums[i - 3] : people[i - 2].c;
      if (third < sums[i]) {
        sums[i] = third;
      }
    }
  }
  std::cout << sums[n - 1];
  delete[] people;
  delete[] sums;
  return 0;
}