#include <cstdint>
#include <iostream>

using std::cin;
using std::cout;
using std::string;

struct Cell {
  int8_t state = 0;  // 0 - empty, 1 - full, 2 - deleted
  string value;
};

size_t MainHash(const string &current_string, size_t table_size) {
  static const uint32_t p = 1'000'000'007;
  static const uint16_t x = 263;

  size_t length = current_string.length();

  uint64_t power_of_x = 1;
  uint64_t hash = 0;

  for (size_t i = 0; i < length; i++) {
    hash += (current_string[i] * power_of_x) % p;
    power_of_x = (power_of_x * x) % p;
  }

  return hash % p % table_size;
}

size_t StepHash(const string &current_string, size_t table_size) {
  uint64_t sum = 0;
  for (size_t i = 0; i < current_string.length(); i++) {
    sum = (sum + (current_string[i] % table_size));
  }
  size_t hash = (1 + sum) % table_size;
  if (hash % 2 == 0 || hash == 0) {
    hash = (hash + 1) % table_size;
  }
  return hash;
}

class HashTable {
 public:
  void Push(string value) {
    if (Search(value) == true) {
  	  return;
    }
    if (Add(table_, value, size_) == false) {
      Resize();
      Add(table_, value, size_);
    }
  }

  bool Search(string value) {
    size_t hash = MainHash(value, size_);
    size_t step = StepHash(value, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t pos = (hash + i * step) % size_;
      if (table_[i].state == 0) {
        return false;
      }
      if (table_[i].value == value && table_[i].state != 2) {
        return true;
      }
    }
    return false;
  }

  bool Remove(string value) {
    size_t hash = MainHash(value, size_);
    size_t step = StepHash(value, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t pos = (hash + i * step) % size_;
      if (table_[i].state == 0) {
        return false;
      }
      if (table_[i].value == value && table_[i].state != 2) {
        table_[i].state = 2;
        return true;
      }
    }
    return false;
  }

 private:
  size_t size_ = 2;
  Cell *table_ = new Cell[size_];

  void Resize() {
    size_t new_size = size_ * 2;
    Cell *new_table = new Cell[new_size];
    for (size_t i = 0; i < size_; i++) {
      if (table_[i].state != 0 && table_[i].state != 2) {
        Add(new_table, table_[i].value, new_size);
      }
    }
    delete[] table_;
    table_ = new_table;
    size_ = new_size;
  }

  bool Add(Cell *table, string value, size_t size) {
    size_t hash = MainHash(value, size);
    size_t step = StepHash(value, size);
    for (size_t i = 0; i < size; i++) {
      size_t pos = (hash + i * step) % size;
      if (table[i].state == 0 || table[i].state == 2) {
        table[i].value = value;
        table[i].state = 1;
        return true;
      }
    }
    return false;
  }
};

int main() {
  HashTable string_table;
  string command;
  while (cin >> command) {
    string input;
    cin >> input;
    if (command == "push") {
      string_table.Push(input);
      continue;
    }
    if (command == "pop") {
      bool in_the_table = string_table.Remove(input);
      if (in_the_table) {
        cout << "TRUE"
             << "\n";
      } else {
        cout << "FALSE"
             << "\n";
      }
      continue;
    }
    if (command == "search") {
      bool in_the_table = string_table.Search(input);
      if (in_the_table) {
        cout << "TRUE"
             << "\n";
      } else {
        cout << "FALSE"
             << "\n";
      }
      continue;
    }
  }
}
