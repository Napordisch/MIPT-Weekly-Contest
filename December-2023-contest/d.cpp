#include <iostream>
using std::cin;
using std::cout;

void Swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}
void SelectionSort(int *arr, int len) {
  for (int i = 0; i < len; i++){
    for (int j = i + 1; j < len; j++) {
      if (arr[i] > arr[j]) {
        Swap(arr[i], arr[j]);
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  int *times = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> times[i];
  }
  SelectionSort(times, n);
  for (int i = 0; i < n; i++) {
    cout << times[i] << " ";
  }
  delete[] times;
  return 0;
}