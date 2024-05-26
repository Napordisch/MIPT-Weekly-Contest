#include <iostream>
#include <string>

template <typename T>
T Min(T first, T second) {
  if (first < second) {
    return first;
  }
  return second;
}

template <typename T>
class Array {
 public:
  explicit Array<T>(unsigned int size) : size_(size) {
    array_ = new T[size_]{0};
  }
  ~Array() {
    delete[] array_;
  }
  T &operator[](unsigned int index) {
    return array_[index];
  }
  unsigned int Size() {
    return size_;
  }

 private:
  unsigned int size_;
  T *array_;
};

struct Segment {
  unsigned int from;
  unsigned int to;
};

class ZFunction {
 public:
  explicit ZFunction(const std::string &s) : z_(s.size()) {
    Calculate(s);
  }

  void Print() {
    for (unsigned int i = 0; i < z_.Size(); ++i) {
      std::cout << z_[i] << ' ';
    }
    std::cout << '\n';
  }

 private:
  Array<unsigned int> z_;
  void Calculate(const std::string &s) {
    unsigned int length = s.size();
    unsigned int l = 0;
    unsigned int r = 0;

    for (unsigned int i = 0; i < length; ++i) {
      if (i <= r) {
        z_[i] = Min(z_[i - l], r - i + 1);
      }

      while (i + z_[i] < length && s[z_[i]] == s[i + z_[i]]) {
        ++z_[i];
      }

      if (i + z_[i] - 1 > r) {
        r = i + z_[i] - 1;
        l = i;
      }
    }
  }
};

int main() {
  std::string s;
  std::cin >> s;
  ZFunction z(s);
  z.Print();
}