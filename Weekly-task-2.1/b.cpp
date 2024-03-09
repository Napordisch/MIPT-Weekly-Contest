#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>

using std::cin;
using std::cout;
using std::string;

size_t Hash(const string &current_string, size_t table_size) {
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

struct Entry {
  std::string string;
  Entry *next = nullptr;
  Entry *prev = nullptr;
};

class Stack {
 public:
  bool IsFree() { return root_ == nullptr; }

  void PushFront(std::string string) {
    Entry *new_entry = new Entry;
    new_entry->string = string;
    new_entry->next = root_;
    if (root_ != nullptr) {
      root_->prev = new_entry;
    }
    root_ = new_entry;
  }

  void Remove(string string) {
    Entry *to_be_removed = Find(string);
    if (to_be_removed == nullptr) {
      return;
    }
    if (to_be_removed->prev != nullptr) {
      to_be_removed->prev->next = to_be_removed->next;
    } else {
      root_ = to_be_removed->next;
    }
    if (to_be_removed->next != nullptr) {
      to_be_removed->next->prev = to_be_removed->prev;
    }
    delete to_be_removed;
  }

  Entry *Find(string string) {
    Entry *runner = root_;
    while (runner != nullptr) {
      if (runner->string == string) {
        break;
      }
      runner = runner->next;
    }
    return runner;
  }

  void Display() {
    Entry *runner = root_;
    while (runner != nullptr) {
      cout << runner->string;
      runner = runner->next;
      if (runner != nullptr) {
        cout << " ";
      }
    }
    cout << "\n";
  }

  ~Stack() {
    while (root_ != nullptr) {
      Entry *new_root = root_->next;
      delete root_;
      root_ = new_root;
    }
  }

 private:
  Entry *root_ = nullptr;
};

int main() {
  size_t m, n;
  cin >> m;
  cin >> n;
  Stack *table = new Stack[m];
  for (size_t i = 0; i < n; i++) {
    string command;
    cin >> command;
    if (command == "add") {
      string string;
      cin >> string;
      size_t hash = Hash(string, m);
      if (table[hash].Find(string) != nullptr) {
        continue;
      }
      table[hash].PushFront(string);
      continue;
    }
    if (command == "check") {
      size_t index;
      cin >> index;
      table[index].Display();
      continue;
    }
    if (command == "find") {
      string string;
      cin >> string;
      size_t hash = Hash(string, m);
      Entry *found_entry = table[hash].Find(string);
      if (found_entry != nullptr) {
        cout << "yes"
             << "\n";
        continue;
      }
      cout << "no"
           << "\n";
      continue;
    }
    if (command == "del") {
      string string;
      cin >> string;
      size_t hash = Hash(string, m);
      table[hash].Remove(string);
      continue;
    }
  }
}