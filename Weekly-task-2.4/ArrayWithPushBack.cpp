class PushPopArray {
public:
  PushPopArray(uint32_t size) {
    if (size_ == 0) {
      return;
    }
    size_ = size;
    array_ = new uint32_t[size];
  }

  ~PushPopArray() {
    delete[] array_;
  }

  void push_back(uint32_t value) {
    array_[index_] = value;
    index_++;
  }

  uint32_t pop_back() {
    index_--;
    return array_[index_ + 1];
  }

  void pop_front() {
    start_++;
    size_--;
  }

  uint32_t operator[](uint32_t index) {
    return array_[index + start_];
  }

  void Reset() {
    index_ = 0;
    start_ = 0;
  }

  uint32_t size() {
    return index_ - start_;
  }

private:
  uint32_t index_ = 0;
  uint32_t *array_ = nullptr;
  uint32_t size_ = 0;
  uint32_t start_ = 0;
};