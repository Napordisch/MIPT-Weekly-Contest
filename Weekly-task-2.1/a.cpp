#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
using std::cin;
using std::cout;

struct Entry {
  std::string name;
  uint32_t number;
  Entry *next = nullptr;
  Entry *prev = nullptr;
};

class Stack {
public:
  bool IsFree() { return root_ == nullptr; }

  void PushFront(uint32_t number, std::string name) {
    Entry *new_entry = new Entry;
    new_entry->number = number;
    new_entry->name = name;
    new_entry->next = root_;
    if (root_ != nullptr) {
      root_->prev = new_entry;
    }
    root_ = new_entry;
  }

  void Remove(uint32_t number) {
    Entry *to_be_deleted = Find(number);
    if (to_be_deleted == nullptr) {
      return;
    }
    if (to_be_deleted->next != nullptr) {
      to_be_deleted->next->prev = to_be_deleted->prev;
    }
    if (to_be_deleted->prev != nullptr) {
      to_be_deleted->prev->next = to_be_deleted->next;
    } else {
      root_ = to_be_deleted->next;
    }
    delete to_be_deleted;
  }

  Entry *Find(uint32_t number) {
    Entry *runner = root_;
    while (runner != nullptr) {
      if (runner->number == number) {
        break;
      }
      runner = runner->next;
    }
    return runner;
  }

  Entry *EjectFront() {
    Entry *to_be_returned = root_;
    root_ = root_->next;
    if (root_ != nullptr) {
      root_->prev = to_be_returned->prev;
    }
    return to_be_returned;
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

size_t Hash(uint32_t number, size_t size) {
  static const double CORMEN_CONST = 0.618034;
  size_t hash = floor(size * (std::fmod((number * CORMEN_CONST), 1)));
  return hash;
}

class Phonebook {
public:
  Phonebook(size_t size = 1000) {
    table_size_ = size;
    table_ = new Stack*[table_size_];
    empty_stacks_ = table_size_;
    for (size_t i = 0; i < table_size_; i++) {
      table_[i] = new Stack;
    }
    
  }
  ~Phonebook() { 
    for (size_t i = 0; i < table_size_; i++) {
      delete table_[i];
    }
    delete[] table_; 
  }

  void Insert(size_t number, std::string name) {
    // if (empty_stacks_ == 0) {
    //   Resize(table_size_ * 2);
    // }  
    size_t hash = Hash(number, table_size_);
    if (table_[hash]->IsFree()) {
      empty_stacks_--;
    }
    table_[hash]->PushFront(number, name);
  }
  
  std::string Find(size_t number) {
    size_t hash = Hash(number, table_size_);
    Entry *the_entry = table_[hash]->Find(number);
    if (the_entry != nullptr) {
      return the_entry->name;
    }
    return "not found";
  }

  void Remove(size_t number) {
    size_t hash = Hash(number, table_size_);
    table_[hash]->Remove(number);
    if (table_[hash]->IsFree()) {
      empty_stacks_++;
    }
  }

private:
  Stack **table_ = nullptr;
  size_t table_size_ = 0;
  size_t empty_stacks_ = table_size_;

  // void Resize(size_t new_size) {
  //   Stack **new_table = new Stack*[new_size];
  //   for (size_t i = 0; i < new_size; i++) {
  //     new_table[i] = new Stack;
  //   }
  //   empty_stacks_ = new_size;
  //   for (size_t i = 0; i < table_size_; i++) {
  //     Stack *cur_stack = table_[i];
  //     while (cur_stack->IsFree() != true) {
  //       Entry *to_transfer = cur_stack->EjectFront();
  //       size_t hash = Hash(to_transfer->number, new_size);

  //       if (new_table[hash]->IsFree()) {
  //         empty_stacks_--;
  //       }

  //       new_table[hash]->PushFront(to_transfer->number, to_transfer->name);
  //       delete to_transfer;
  //     }
  //   }
  //   table_size_ = new_size;
  //   delete[] table_;
  //   table_ = new_table;
  // }
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
