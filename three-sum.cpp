//
//  main.cpp
//  three_sum
//
//  Created by William McCarthy on 217//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "stopwatch.h"
#include "sorts_searches.h"

#include "three_sum_bfmi.h"
#include "three_sum_shellbinary.h"


int main(int argc, const char * argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./three_sum inputfile\n";
    exit(ARGC_ERROR);
  }
  std::string filename = argv[1];
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cerr << "Could not open filename: '" << filename << "'\n";
    exit(FILE_ERROR);
  }

//  array_expand<int>::run_tests();
  
  three_sum_bfmi ts(2);
//  three_sum_shellbinary ts(2);
  ifs >> ts;
  ts.count_triples();
  
  return 0;
}


