// void Merge(const int32_t* l, size_t l_len, const int32_t* r, size_t r_len, int32_t* buffer) {
//   size_t l_index = 0;
//   size_t r_index = 0;
//   // with comparison
//   while (l_index < l_len && r_index < r_len) {
//     if (l[l_index] >= r[r_index]) {
//       buffer[l_index + r_index] = l[l_index];
//       l_index++;
//     } else {
//       buffer[l_index + r_index] = r[r_index];
//       r_index++;
//     }
//   }
//   // if r_len > l_len or l_len > r_len
//   while (l_index < l_len) {
//     buffer[l_index + r_index] = l[l_index];
//     l_index++;
//   }
//   while (r_index < r_len) {
//     buffer[l_index + r_index] = r[r_index];
//     r_index++;
//   }
// }

// void RecursiveMergeSort(int32_t* arr, size_t n, int32_t* buffer) {
//   if (n <= 1) {
//     return;
//   }
//   size_t middle = n / 2;
//   RecursiveMergeSort(arr, middle, buffer);
//   RecursiveMergeSort(arr + middle, n - middle, buffer);
//   Merge(arr, middle, arr + middle, n - middle, buffer);
//   for (size_t i = 0; i < n; i++) {
//     arr[i] = buffer[i];
//   }
// }

// void MergeSort(int32_t* arr, size_t n) {
//   int32_t* buffer = new int32_t[n];
//   RecursiveMergeSort(arr, n, buffer);
//   delete[] buffer;
// }