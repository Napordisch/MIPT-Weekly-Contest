#include <iostream>
#include <string>

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

class PrefixFunction {
 public:
  explicit PrefixFunction(const std::string &s) : p_(s.size()), string_length_(s.size()) {
    Calculate(s);
  }
  unsigned int Size() {
    return p_.Size();
  }
  void Print() {
    for (unsigned int i = 0; i < string_length_; ++i) {
      std::cout << p_[i] << ' ';
    }
    std::cout << '\n';
  }

 private:
  Array<unsigned int> p_;
  unsigned int string_length_ = 0;

  void Calculate(const std::string &s) {
    for (unsigned int i = 1; i < string_length_; ++i) {
      unsigned int k = p_[i - 1];
      while (s[i] != s[k] && k > 0) {
        k = p_[k - 1];
      }
      if (s[i] == s[k]) {
        p_[i] = k + 1;
      }
    }
  }
};

int main() {
  using std::cin;
  using std::cout;
  using std::string;
  string s;
  cin >> s;
  PrefixFunction pi(s);
  pi.Print();
}