#include <iostream>

using std::cin;
using std::cout;

void Swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

struct ASwap {
  int from;
  int to;
  ASwap *next = nullptr;
};

void NewSwap(ASwap *&root_swap, int from, int to) {
  if (root_swap == nullptr) {
    root_swap = new ASwap;
    root_swap->from = from;
    root_swap->to = to;
    return;
  }
  ASwap *runner = root_swap;
  while (runner->next != nullptr) {
    runner = runner->next;
  }
  runner->next = new ASwap;
  runner->next->from = from;
  runner->next->to = to;
}


void SiftDown(int *heap, int n, int &swaps_amount, ASwap *&root_swap, int *swaps) {
  for (int i = 0; i < n; i++) {
    int min = i;
    int left_child_i = 2 * i + 1;
    int right_child_i = 2 * i + 2;
    if (heap[left_child_i] < heap[min]) {
      min = left_child_i;
    }
    if (heap[right_child_i] < heap[min]) {
      min = right_child_i;
    }
    if (min != i) {
      Swap(heap[min], heap[i]);
      swaps_amount++;
      // NewSwap(root_swap, min, i);
    }
  }
}
void ShowSwaps(ASwap *root_swap) {
  ASwap *runner = root_swap;
  while (runner != nullptr) {
    cout << runner->from;
    cout << runner->to;
    runner = runner->next;
  }
}
int main() {
  int n;
  int *sweets = new int[n];
  int swaps_amount = 0;
  int *swaps = new int[n];
  ASwap *root_swap = nullptr;
  for(int i = 0; i < n; i++) {
    cin >> sweets[i];
  }
  SiftDown(sweets, n, swaps_amount, root_swap, swaps);
  cout << swaps_amount;
  if (swaps_amount!=0) {
    ShowSwaps(root_swap);
  }
}