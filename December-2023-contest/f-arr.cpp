#include <iostream>

using std::cin;
using std::cout;

void Swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

void SiftDown(int *heap, int n, int &swaps_amount, int *swaps) {
  for (int i = 0; i < n; i++) {
    int min = i;
    if (2 * i + 1 <= n - 1) {
      if (heap[2 * i + 1] < heap[min]){
        min = 2 * i + 1;
      }
    }
    if (2 * i + 2 <= n - 1) {
      if (heap[2 * i + 2] < heap[min]){
        min = 2 * i + 2;
      }
    }
    if (min != i) {
      Swap(heap[min], heap[i]);
      swaps[swaps_amount * 2] = min;
      swaps[swaps_amount * 2 + 1] = i;
      swaps_amount++;
    }


    // if (2 * i + 1 < n - 1) {
    // // int left_child_i = 2 * i + 1;
    // //   if (heap[left_child_i] < heap[min]) {
    // //     min = left_child_i;
    // //   }
    //   if (heap[i] >= heap[2 * i + 1]){
    //     Swap(heap[i], heap[2 * i + 1]);
    //     swaps_amount++;
    //     swaps[swap_index * 2] = i;
    //     swaps[swap_index * 2 + 1] = 2 * i + 1;
    //     swap_index++;
    //   }
    // }

    // if (2 * i + 2 < n - 1) {
    //   // int right_child_i = 2 * i + 2;
    //   // if (heap[right_child_i] < heap[min]) {
    //   //   min = right_child_i;
    //   // }
    //   if (heap[i] >= heap[2 * i + 2]){
    //     Swap(heap[i], heap[2 * i + 2]);
    //     swaps_amount++;
    //     swaps[swap_index * 2] = i;
    //     swaps[swap_index * 2 + 1] = 2 * i + 2;
    //     swap_index++;
    //   }
    // }
    // // if (min != i) {
    // //   Swap(heap[min], heap[i]);
    // //   swaps_amount++;
    // //   swaps[swap_index * 2] = min;
    // //   swaps[swap_index * 2 + 1] = i;
    // //   swap_index++;
    // // }
  }
}
int main() {
  int n;
  cin >> n;
  int *sweets = new int[n];
  int swaps_amount = 0;
  int *swaps = new int[n * 2];
  for(int i = 0; i < n; i++) {
    cin >> sweets[i];
  }
  // SiftDown(sweets, n, swaps_amount, swaps);
  for (int i = 0; i < n; i++) {
    int min = i;
    if (i * 2 + 1 <= n - 1) {
      if (sweets[i * 2 + 1] < sweets[min]) {
        min = i * 2 + 2;
      }
    } 
    if (i * 2 + 2 <= n - 1) {
      if (sweets[i * 2 + 2] < sweets[min]) {
        min = i * 2 + 2;
      }
    } 
    if (min != )
  }
  cout << swaps_amount << "\n";
  for (int i = 0; i < swaps_amount; i++) {
    cout << swaps[i * 2] << " ";
    cout << swaps[i * 2 + 1] << "\n";
  }
}