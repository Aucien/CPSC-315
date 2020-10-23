//
//  array_expand.h
//  three_sum
//
//  Created by William McCarthy on 079//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef array_expand_h
#define array_expand_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>

#define ARGC_ERROR 1
#define FILE_ERROR 2

//-------------------------------------------------------------------------
//
template <typename T>
class array_expand {       // this class allocates dynamic memory
private:
  size_t size_;
  size_t capacity_;
  T* values_;
  
protected:
  constexpr static size_t MIN_CAPACITY = 4;

public:
  array_expand() : array_expand(MIN_CAPACITY) { }
  array_expand(size_t capacity)
  : size_(0), capacity_(capacity), values_(new T[capacity]) {
    std::fill(values_, values_ + capacity_, T());
  }
  
//                         // initializer_list constructor and init_list assignment operator
  array_expand(const std::initializer_list<T>& li)
    : array_expand(li.size()) { *this = li; }
  array_expand& operator=(const std::initializer_list<T>& li) {
    std::copy(li.begin(), li.end(), values_);
    size_ = li.size();
    return *this;
  }

  // copy constructor, assignment operator and destructor
  array_expand(const array_expand& other)
    : array_expand() { copy(other); }
  array_expand& operator=(const array_expand& other) {
    if (this != &other) { copy(other); }
    return *this;
  }
  
                          // move constructor, and move assignment operator
  array_expand(array_expand&& other)
    : array_expand() { move(std::move(other)); }
  array_expand& operator=(array_expand&& other) {
    if (this != &other) { move(std::move(other)); }
      return *this;
  }

  virtual ~array_expand() { delete[] values_; }
  
  void append(const T& value) { values_[size_++] = value; }
  
  size_t size() const { return size_; }
  bool empty() const  { return size_ == 0; }
  T* values() const { return values_; }

  friend std::istream& operator>>(std::istream& is, array_expand& ae) {
    T value;
    T* p = ae.values_;
    std::fill(p, p + ae.capacity_, T());
    while (is >> value) {
      ae.check_overflow();
      ae.values_[ae.size_++] = value;
    }
    return is;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const array_expand& ae) {
    if (ae.empty()) { return os << "array_expand is empty\n"; }

    const T* p = ae.values_;
    size_t len = ae.size_;
    for (size_t i = 0; i < len; ++i) {
      os << p[i] << " ";
    }
    return os;
  }

  void copy(const array_expand& other) {
    if (values_ != nullptr) { delete[] values_; }

    size_ = other.size_;
    capacity_ = other.capacity_;
    values_ = new T[capacity_];
    std::copy(other.values_, other.values_ + capacity_, values_);
  }
  void move(array_expand&& other) {
    if (values_ != nullptr) { delete[] values_; }

    size_ = other.size_;
    capacity_ = other.capacity_;
    values_ = other.values_;
    
    other.size_ = 0;
    other.capacity_ = 0;
    other.values_ = nullptr;
  }
  
  static void run_tests() {
    array_expand<int> ae = { 1, 2, 3, 4, 5 };
    std::cout << "ae is: " << ae << "\n";

    ae.append(20);
    std::cout << "and after appending 20, ae is: " << ae << "\n";
  }

private:
  void print(T* p, size_t size) {
    for (size_t i = 0; i < size; ++i) { std::cout << p[i] << " "; }
    std::cout << "\n";
  }
  void resize(size_t capacity) {
    static bool first_time = true;
    if (first_time) { std::cout << "\nresizing to ";  first_time = false; }
    std::cout << capacity << "... ";
    T* newvalues = new T[capacity];
    
    std::copy(values_, values_ + capacity_, newvalues);          // 0 1 2 3  cap: 4
    std::fill(newvalues + capacity_, newvalues + capacity, T());   // 0 1 2 3 4 5 6 7 cap: 8

    capacity_ = capacity;
    delete[] values_;
    values_ = newvalues;
  }
  void check_underflow() {
    if (size_ == 0) { throw new std::underflow_error("underflow\n"); }
    if (size_ <= capacity_ / 4) { resize(capacity_ / 2); }
  }
  void check_overflow()  {
    if (size_ == capacity_) { resize(2 * capacity_); }
  }
};

#endif /* array_expand_h */
