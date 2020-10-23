//
//  three_sum.h
//  three_sum
//
//  Created by William McCarthy on 059//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef three_sum_h
#define three_sum_h

#include "array_expand.h"


class three_sum {       // this class allocates dynamic memory
private:
  array_expand<int> ae_;

protected:
  constexpr static size_t MIN_CAPACITY = 4;

public:
  three_sum() : three_sum(MIN_CAPACITY) { }
  three_sum(size_t capacity) : ae_(capacity) { }
  
                         // initializer_list constructor and init_list assignment operator
  three_sum(const std::initializer_list<int>& li) : three_sum(li.size()) { *this = li; }
  three_sum& operator=(const std::initializer_list<int>& li) {  ae_ = li;  return *this; }
                                 // copy constructor, assignment operator and destructor
                                 // don't need these -- our class only has expand_access,
                                 // which has a valid copy ctor, assignment operator, AND
                                 // move ctor and move assignment operator
//  three_sum(const three_sum& other) : three_sum() { copy(other); }
//  three_sum& operator=(const three_sum& other) {
//    if (this != &other) { copy(other); }
//    return *this;
//  }
                          // move constructor, and move assignment operator
//  three_sum(three_sum&& other) : three_sum() { move(std::move(other)); }
//  three_sum& operator=(three_sum&& other) {
//    if (this != &other) { move(std::move(other)); }
//    return *this;
//  }

  virtual ~three_sum() { }
  virtual size_t count() = 0;                 // pure virtual method (abstract)

  size_t size() const { return ae_.size(); }
  bool empty() const  { return ae_.size() == 0; }
  int* values() const { return ae_.values(); }

  void count_triples() {
    stopwatch sw("triples", 6);

    sw.start();
    std::cout << "\ncounting_triples for size " << size() << "...\n";

    size_t triples = count();
    sw.stop();

    std::cout << "\nIn this file there are...\n\t";
    std::cout << triples << " triples  (summing to 0)\n\n";
    std::cout << sw << "\n\n";
  }

  friend std::istream& operator>>(std::istream& is, three_sum& three) { return is >> three.ae_; }

  friend std::ostream& operator<<(std::ostream& os, const three_sum& three) {
    return os << three.ae_;
  }

protected:
  void copy(const three_sum& other) { ae_.copy(other.ae_); }
  void move(three_sum&& other)      { ae_.move(std::move(other.ae_)); }
};


#endif /* three_sum_h */
