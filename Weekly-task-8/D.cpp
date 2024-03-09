#include <iostream>
void Merge(const uint32_t* l, size_t l_len, const uint32_t* r, size_t r_len, uint32_t* buffer) {
  size_t l_index = 0;
  size_t r_index = 0;
  // with comparison
  while (l_index < l_len && r_index < r_len) {
    if (l[l_index] <= r[r_index]) {
      buffer[l_index + r_index] = l[l_index];
      l_index++;
    } else {
      buffer[l_index + r_index] = r[r_index];
      r_index++;
    }
  }
  // if r_len > l_len or l_len > r_len
  while (l_index < l_len) {
    buffer[l_index + r_index] = l[l_index];
    l_index++;
  }
  while (r_index < r_len) {
    buffer[l_index + r_index] = r[r_index];
    r_index++;
  }
}

void RecursiveMergeSort(uint32_t* arr, size_t n, uint32_t* buffer) {
  if (n <= 1) {
    return;
  }
  size_t middle = n / 2;
  RecursiveMergeSort(arr, middle, buffer);
  RecursiveMergeSort(arr + middle, n - middle, buffer);
  Merge(arr, middle, arr + middle, n - middle, buffer);
  for (size_t i = 0; i < n; i++) {
    arr[i] = buffer[i];
  }
}

void MergeSort(uint32_t* arr, size_t n) {
  uint32_t* buffer = new uint32_t[n];
  RecursiveMergeSort(arr, n, buffer);

  delete[] buffer;
}

bool UseBanknotes(uint32_t s, uint32_t* banknotes, uint32_t n, uint32_t top) {
  using std::cin;
  using std::cout;

  uint32_t amount_of_banknotes = 0;
  auto* banknotes_used = new uint32_t[n];
  for (uint32_t i = 0; i < n; i++) {
    banknotes_used[i] = 0;
  }

  uint32_t remainder = s;
  for (uint32_t i = top; i + 1 > 0; i--) {
    if (banknotes[i] > remainder) {
      continue;
    }
    banknotes_used[i] = remainder / banknotes[i];
    amount_of_banknotes += remainder / banknotes[i];
    remainder = remainder % banknotes[i];

    if (remainder == 0) {
      cout << amount_of_banknotes << "\n";
      for (uint32_t i = 0; i < n; i++) {
        if (banknotes_used[i] != 0) {
          cout << banknotes[i] << " ";
        }
      }
      delete[] banknotes_used;
      return true;
    }
  }
  delete[] banknotes_used;
  return false;
}

int main() {
  using std::cin;
  using std::cout;

  uint32_t n;
  uint32_t s;
  cin >> n >> s;
  auto* banknotes = new uint32_t[n];
  for (size_t i = 0; i < n; i++) {
    cin >> banknotes[i];
  }
  MergeSort(banknotes, n);

  // no banknotes are used yet
  for (uint32_t top = n - 1; top + 1 > 0; top--) {
    if (UseBanknotes(s, banknotes, n, top)) {
      delete[] banknotes;
      return 0;
      break;
    }
  }
  delete[] banknotes;
  cout << -1;
  return 0;
}