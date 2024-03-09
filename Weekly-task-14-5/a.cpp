#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
template <typename T>
static T min(T a, T b) {
  if (a < b) {
    return a;
  }
  return b;
}

int log2_fast(int n) {
    float d = static_cast<float>(n);
    int result;
    std::frexp(d, &result);
    return result;
}

void SparseTableFill(int **sparse_table, size_t len, size_t columns, int *array) {
  for (size_t i = 0; i < len; i++) {
    sparse_table[i][0] = array[i];
  }

  int delta = 1;
  for (size_t k = 1; k < columns; k++) {
    for (size_t i = 0; i < len; i++) {
      if (i + delta < len) {
        sparse_table[i][k] = min(sparse_table[i][k - 1], sparse_table[i + delta][k - 1]);
      } else {
        sparse_table[i][k] = sparse_table[i][k - 1];
      }
    }
    delta *= 2;
  }
}

int RangeMinimumQuerry(int **sparse_table, size_t len, size_t left, size_t right){
    // int k = 0;
    // size_t max2k = 1;
    // while (max2k * 2 <= right - left + 1) {
    //   k++;
    //   max2k *= 2;
    // }
    int k = std::log2(right - left + 1);
    size_t max2k = std::pow(2, k);
    int j = right - max2k + 1;
    return min(sparse_table[left][k], sparse_table[j][k]);
}


static void SparseTableOutput(int **sparse_table, size_t len, size_t columns) {
  for (size_t i = 0; i < len; i++) { 
    for (size_t j = 0; j < columns; j++) {
      cout << sparse_table[i][j] << " ";
    }
    cout << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  size_t len;
  cin >> len;
  int *array = new int[len];
  size_t columns = static_cast<size_t>(log2_fast(len));
  for (size_t i = 0; i < len; i++) {
    cin >> array[i];
  }

  int **sparse_table = new int *[len];
  for (size_t i = 0; i < len; i++) {
    sparse_table[i] = new int[columns];
  }


  SparseTableFill(sparse_table, len, columns, array);

 // querries
 std::string command;
 while (cin >> command) {
  if (command == "min") {
    size_t left, right;
    cin >> left >> right;
    cout << RangeMinimumQuerry(sparse_table, len, left - 1, right - 1) << "\n";
  }
  if (command == "set") {
    size_t i;
    cin >> i;
    int x;
    cin >> x;
    array[i - 1] = x;
    SparseTableFill(sparse_table, len, columns, array);
  }  
  if (command == "output") {
    SparseTableOutput(sparse_table, len, columns);
  } 
 }
}
