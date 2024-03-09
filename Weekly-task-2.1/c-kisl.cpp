#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

using std::cin;
using std::cout;
using std::string;

struct Cell {
  int8_t state = 0;  // 0 — empty, 1 – full, 2 — deleted
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

  hash = hash % p;
  size_t exported_hash = hash % table_size;
  return exported_hash;
}

size_t StepHash(const string &current_string, size_t table_size) {
  static const uint32_t p = 1'000'000'009;
  static const uint16_t x = 107;

  size_t length = current_string.length();

  uint64_t power_of_x = 1;
  uint64_t hash = 0;

  for (size_t i = 0; i < length; i++) {
    hash += (current_string[i] * power_of_x);
    power_of_x = (power_of_x * x) % p;
  }
  hash = hash % p;
  size_t exported_hash = hash % table_size;
  while (exported_hash == 0) {
    hash += 1;
    exported_hash = hash % table_size;
  }
  return exported_hash;
}
class HashTable {
 public:
  bool Find(string value) {
    size_t hash = MainHash(value, size_);
    size_t step = StepHash(value, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t pos = (hash + i * step) % size_;
      if (table_[pos].state != 2 && table_[pos].value == value) {
        return true;
      } else if (table_[pos].state == 0) {
        return false;
      }
    }
    return false;
  }
  bool Remove(string value) {
    size_t hash = MainHash(value, size_);
    size_t step = StepHash(value, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t pos = (hash + step * i) % size_;
      if (table_[pos].state != 2 && table_[pos].value == value) {
        table_[pos].state = 2;
        return true;
      }
      if (table_[pos].state == 0) {
        return false;
      }
    }
    del_counter_++;
    counter_--;
    return false;
  }

  void Push(string value) {
    if (counter_ > size_ * 0.75) {
      Resize();
    }
    if (del_counter_ > 0.5 * counter_) {
      Resize(1);
    }
    Insert(table_, value);
    counter_++;
  }

 private:
  size_t size_ = 2;
  Cell *table_ = new Cell[size_];
  size_t counter_ = 0;
  size_t del_counter_ = 0;

  void Resize(size_t coefficient = 2) {
    size_t new_size = size_ * coefficient;
    Cell *new_table = new Cell[new_size];
    for (size_t i = 0; i < size_; i++) {
      if (table_[i].state == 1) {
        Insert(new_table, table_[i].value);
      }
    }
    size_ = new_size;
    delete[] table_;
    table_ = new_table;
  }
  void Insert(
      Cell *table,
      string value) {  // receieves table argument to insert in new tables
    size_t hash = MainHash(value, size_);
    size_t step = StepHash(value, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t pos = (hash + step * i) % size_;
      if (table[pos].state == 0) {
        table[pos].value = value;
        table[pos].state = 1;
        return;
      } else if (table[pos].state == 2) { // should happen only in original table
        if (Find(value) == false) {
          table[pos].state = 1;
          table[pos].value = value;
          del_counter_--;
          return;
        }
      }
    }
  }
};

int main() {
  HashTable string_table;
  uint64_t cycles;
  cin >> cycles;
  for (uint64_t i = 0; i < cycles; i++) {
    string command;
    cin >> command;
    string input;
    cin >> input;
    if (command == "push") {
      string_table.Push(input);
      // cout << "\n" << "Current table:" << "\n";
      // string_table.Display();
      // cout << "\n";
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
      bool in_the_table = string_table.Find(input);
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
