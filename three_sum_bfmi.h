//
//  three_sum_bfmi.h
//  three_sum
//
//  Created by William McCarthy on 049//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef three_sum_bfmi_h
#define three_sum_bfmi_h

#include "three_sum.h"

class three_sum_bfmi : public three_sum {       // bfmi variant of three_sum
public:
  three_sum_bfmi() : three_sum_bfmi(MIN_CAPACITY) { }
  three_sum_bfmi(size_t capacity) : three_sum(capacity) { }
  
//                         // initializer_list constructor and init_list assignment operator
  three_sum_bfmi(const std::initializer_list<int>& li) : three_sum(li) { *this = li; }
  three_sum_bfmi& operator=(const std::initializer_list<int>& li) {
    three_sum* ts = dynamic_cast<three_sum*>(this);
    *ts = li;
    return *this;
  }
                                 // copy constructor, assignment operator and destructor
  three_sum_bfmi(const three_sum_bfmi& other) : three_sum(other) { }
  three_sum_bfmi& operator=(const three_sum_bfmi& other) {
    three_sum* ts = dynamic_cast<three_sum*>(this);
    *ts = other;
    return *this;
  }
  
//                          // move constructor, and move assignment operator
  three_sum_bfmi(three_sum_bfmi&& other) : three_sum() { move(std::move(other)); }
  three_sum& operator=(three_sum_bfmi&& other) {
    three_sum* ts = dynamic_cast<three_sum*>(this);
    *ts = other;
    return *this;
  }

  virtual ~three_sum_bfmi() { }

  virtual size_t count()  override {
    std::cout << "...using count_bfmi -- triple loop (very slow)\n";
    size_t ntriples = 0;
    size_t len = size();
    int* p = values();

  //    print(p, size_);
    for (size_t i = 0; i < len; ++i) {
      for (size_t j = i + 1; j < len; ++j) {
        for (size_t k = j + 1; k < len; ++k) {
          if (p[i] + p[j] + p[k] == 0) {
            ++ntriples; }
        }
      }
    }
    return ntriples;
  }
  
  friend std::istream& operator>>(std::istream& is, three_sum_bfmi& three) {
    return is >> dynamic_cast<three_sum&>(three);
  }
  
  friend std::ostream& operator<<(std::ostream& os, const three_sum_bfmi& three) {
    return os << dynamic_cast<const three_sum&>(three);
  }
};


#endif /* three_sum_bfmi_h */
