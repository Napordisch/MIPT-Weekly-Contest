#include <iostream>

struct person {
    uint32_t a;
    uint32_t b;
    uint32_t c;
  };

uint32_t MinTime(person* queue, uint32_t n, uint32_t i, uint32_t sum) {
  uint32_t min;
  //a
  uint32_t a = queue[i].a;
  if (i < n - 1) {
    a = MinTime(queue, n, i + 1, queue[i].a + sum);
  }
  min = a;

  //b
  if (i < n - 1) {
    uint32_t b = queue[i].b;
    if (i < n - 2) {
      b = MinTime(queue, n, i + 2, queue[i].b + sum);
    }
    if (b < min) {
      min = b;
    }
  }

  //c
  if (i < n - 2) {
    uint32_t c = queue[i].c;
    if (i < n - 3) {
      c = MinTime(queue, n, i + 3, queue[i].c + sum);  
    }
    if (c < min) {
      min = c;
    }
  }
  // std::cout << min << "\n";
  return min + sum;
}

int main() {
  using std::cin;
  using std::cout;

  uint32_t n;
  cin >> n;
  person* queue = new person[n];
  for (uint32_t i = 0; i < n; i++) {
    cin >> queue[i].a >> queue[i].b >> queue[i].c;
  }
  uint32_t i = 0;
  uint32_t sum = 0;
  // cout << "Process:" << "\n";
  uint32_t min = MinTime(queue, n, i, sum);
  cout << "Result: ";
  cout << min;

  delete [] queue;
  return 0;
}