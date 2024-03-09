#include <iostream>

using std::cin;
using std::cout;

template <typename Type>
class Array {
  public:
    Array(size_t x_size, size_t y_size = 0) {
      x_size_ = x_size;
      y_size_ = y_size;
      if (y_size != 0) {
        dimensions_ = 2;
      }

      if (dimensions_ == 2) {
        array_ = new Type*[x_size_];
        for (size_t i = 0; i < x_size_; ++i) {
          array_[i] = new Type[y_size];
        }
      }

      if (dimensions_ == 1) {
        array_ = new Type*;
        *array_ = new Type[x_size_];
      }

    }

    ~Array() {
      if (dimensions_ == 2) {
        for (size_t i = 0; i < x_size_; ++i) {
          delete[] array_[i];
        }
        delete[] array_;
      }

      if (dimensions_ == 1) {
        delete[] array_;
      }

    }

    Type *operator[](size_t index) {
      return array_[index];
    }

  private:
    size_t x_size_;
    size_t y_size_;
    int16_t dimensions_ = 1;
    Type **array_ = nullptr;

};

int main() {
  Array<int> arr(5);
  arr[3] = 3;


}
