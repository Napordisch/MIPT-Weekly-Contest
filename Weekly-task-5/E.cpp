#include <iostream>

int32_t KOfTheSequence(uint64_t k) {
  int8_t *sequence = new int8_t[k];
  sequence[0] = 0;
  // std::cout << sequence[0] << "\n";
  uint64_t to_read_until = 0;
  uint64_t read_pos = 0;
  for (uint64_t i = 1; i < k; i++) {
    // std::cout << "to_read_until: " << to_read_until << "\n";
    // std::cout << "read_pos: " << read_pos << "\n";

    // position
    std::cout << "n: " << i+1 << "\tread_pos: " << read_pos + 1 << "\tn / 2 + 1 = " << (i + 1) / 2 + 1 << "\tn / 2: " << (i + 1) / 2 <<"\n";
    if (sequence[read_pos] < 2) {
      sequence[i] = sequence[read_pos] + 1;
      // std::cout << sequence[i] << "\n";
    } else {
      sequence[i] = 0;
      // std::cout << sequence[i] << "\n";
    }

    // number
    if (read_pos < to_read_until) {
      read_pos++;
    } else {
      to_read_until += read_pos + 1;
      read_pos = 0;
    }
  }
  int32_t result = sequence[k - 1];
  // delete[] sequence;
  return result;
}

// int32_t KOfTheSequence(uint64_t k) {
//   if (k == 1) {
//     return 0;
//   }

//   if (k % 2 != 0) {
//     return KOfTheSequence(k / 2 + 1);
//   }

//   int32_t a = KOfTheSequence(k / 2) + 1;
//   if (a > 2) {
//     return 0;
//   }
//   return a;
// }

int main() {
  uint64_t k;
  std::cin >> k;
  std::cout << KOfTheSequence(k);
  return 0;
}

// test

// int main() {
//   for (uint64_t i = 1000000000000; i <= 1000000000000000000; i++) {
//       std::cout << i << ": " << KOfTheSequence(i) << "\n";
//   }
//   return 0;
// }