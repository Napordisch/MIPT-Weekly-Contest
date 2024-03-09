#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
using std::cin;
using std::cout;

class Phonebook {
 public:
  void Insert(uint32_t number, std::string name) {
    table_[number] = new std::string;
    *(table_[number]) = name;
  }
  std::string Find(uint32_t number) {
    return *(table_[number]);
  }
  void Remove(uint32_t) {
    delete table_[number];
  }
 private:
  std::string **table_ = new std::string *[1e9];
};

int main() {
  Phonebook my_phonebook;
  size_t n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    std::string command;
    cin >> command;
    if (command == "add") {
      uint32_t number;
      std::string name;
      cin >> number;
      cin >> name;
      my_phonebook.Remove(number);
      my_phonebook.Insert(number, name);
    }
    if (command == "del") {
      uint32_t number;
      cin >> number;
      my_phonebook.Remove(number);
    }
    if (command == "find") {
      uint32_t number;
      cin >> number;
      cout << my_phonebook.Find(number) << "\n";
    }
  }
}
