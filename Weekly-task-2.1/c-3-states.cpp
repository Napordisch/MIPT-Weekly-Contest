#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

using std::cin;
using std::cout;
using std::string;

class BoolVictor {
 public:
  BoolVictor() : size_(0), maasiv(nullptr) {}
  BoolVictor(bool value) {
    size_ = value;
    maasiv = new bool[size_];
  }

  void Insert(int position, bool value) {
    while (position >= size_) {
      Resize(position * 2);
    }
    maasiv[position] = value;
  }

  bool GetValue(int position) {
    while (position >= size_) {
      Resize(position * 2);
    }
    return maasiv[position];
  }

  ~BoolVictor() { delete[] maasiv; }

  void Display() {
    for (size_t i = 0; i < size_; i++) {
      cout << maasiv[i] << " ";
    }
    cout << "\n";
  }

 private:
  size_t size_ = 0;
  bool *maasiv;

  void Resize(size_t new_size) {
    bool *new_array = new bool[new_size]{0};
    for (size_t i = 0; i < size_; i++) {
      new_array[i] = maasiv[i];
    }
    delete[] maasiv;
    size_ = new_size;
    maasiv = new_array;
  }
};

uint64_t SieveOfEratosthenes(uint64_t num) {
  static BoolVictor is_primes;

  uint64_t p = 2;
  while (p * p <= num) {
    if (is_primes.GetValue(p) == false) {
      for (uint64_t i = p * p; i < num + 1; i += p) {
        is_primes.Insert(i, false);
      }
    }
    p += 1;
  }
  uint64_t i = num;
  bool maybe_prime = is_primes.GetValue(i);
  while (maybe_prime == true) {
    i--;
    maybe_prime = is_primes.GetValue(i);
  }
  return i;
}

struct Cell {
  string value;
  bool state = 0;
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
  ~HashTable() { delete[] table_; }
  void Push(string string) {
    if (counter_ >= size_ * 0.75) {
      Resize();
    }
    if (del_counter_ >= counter_ * 0.5) {
      Resize(1);
    }
    Add(table_, string, size_);
    counter_++;
  }

  void Display() {
    for (size_t i = 0; i < size_; i++) {
      cout << table_[i].value << "\n";
    }
  }
  bool IsInTheTable(string string) {
    size_t hash = MainHash(string, size_);
    size_t step = StepHash(string, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t position = (hash + step * i) % size_;

      if (table_[position].state == 0) {
        return false;
      }

      if (table_[position].state != 2 && table_[position].value == string) {
        return true;
      } 

    }
    return false;
  }
  bool Remove(string string) {
    size_t hash = MainHash(string, size_);
    size_t step = StepHash(string, size_);
    for (size_t i = 0; i < size_; i++) {
      size_t position = (hash + step * i) % size_;
      if (table_[position].state == 0) {
        return false;
      }

      if (table_[position].state == 1 && table_[position].value == string) {
        table_[position].state = 2;
        return true;
        counter_--;
        del_counter_++;
      }
    }
    return false;
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
      string string_to_be_copied = table_[i].value;
      if (table_[i].state == 1 && string_to_be_copied != "") {
        Add(new_table, string_to_be_copied, new_size);
      }
    }
    delete[] table_;
    table_ = new_table;
    size_ = new_size;
  }

  void Add(Cell *table, string string, size_t size) {
    size_t hash = MainHash(string, size);
    size_t step = StepHash(string, size);
    for (size_t i = 0; i < size_; i++) {
      size_t position = (hash + step * i) % size;
      if (table[position].state == 0) {
        table[position].value = string;
        table[position].state = 1;
        break;
      }
      else if (table[position].state == 2) {
        if (IsInTheTable(string) == false) {
          table[position].state = 1;
          table[position].value = string;
          del_counter_--;
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
      bool in_the_table = string_table.IsInTheTable(input);
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