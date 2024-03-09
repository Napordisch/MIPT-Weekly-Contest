#include <iostream>

class victor {
 public:
  victor() : size_(0), maasiv(nullptr) {}
  victor(bool value) {
    size_ = value;
    maasiv = new bool[size_];
  }

  void Insert(int position, bool value) {
    if (position >= size_) {
      Resize(position * 2);
    }
    maasiv[position] = value;
  }

  bool GetValue(int position) {
    if (position < size_) {
      return maasiv[position];
    } else {
      std::cerr << "Index out of bounds" << std::endl;
      return -1;  // or some default value indicating error
    }
  }

 private:
  size_t size_ = 0;
  bool* maasiv;

  void Resize(size_t new_size) {
    bool* new_array = new bool[new_size]{0};
    for (size_t i = 0; i < size_; i++) {
      new_array[i] = maasiv[i];
    }
    delete[] maasiv;
    size_ = new_size;
    maasiv = new_array;
  }
};

int main() {
  victor vector;

  vector.Insert(4, true);
  vector.Insert(5, false);
  vector.Insert(6, true);
  vector.Insert(7, false);
  vector.Insert(8, true);
  vector.Insert(9, true);
  std::cout << vector.GetValue(5) << "\n";
  std::cout << vector.GetValue(6) << "\n";
  std::cout << vector.GetValue(7) << "\n";
  std::cout << vector.GetValue(8) << "\n";
  std::cout << vector.GetValue(9) << "\n";
}