#include <iostream>

struct person {
    uint32_t a;
    uint32_t b;
    uint32_t c;
  };

int main() {
  using std::cin;
  using std::cout;

  uint32_t n;
  cin >> n;
  person* queue = new person[n];
  for (uint32_t i = 0; i < n; i++) {
    cin >> queue[i].a >> queue[i].b >> queue[i].c;
  }
  uint32_t* times = new uint32_t[n];
  uint32_t start = n - 1;
  uint32_t end = n > 5 ? start - 5 : 0;
  while (end >= 0) {
    for (uint32_t i = start; i >= end; i--) {
      if (i == start) {
        
      }
    }
    start--;
    end--;
  }
  uint32_t sum = 0;
  // cout << "Process:" << "\n";
  uint32_t min = MinTime(queue, n, i, sum);
  cout << "Result: ";
  cout << min;

  delete [] queue;
  return 0;
}