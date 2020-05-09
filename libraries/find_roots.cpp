#include "main_libraries.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

int main(int argc, char **argv){
  double a = std::strtod(argv[1], NULL);
  double b = std::strtod(argv[2], NULL);
  int tmp = std::atoi(argv[3]);
  bool find;
  if (tmp == 0){
    find = false;
  }
  else{
    find = true;
  }
  double prec = std::strtod(argv[4], NULL);
  double error = std::strtod(argv[5], NULL);
  std::vector<float> res = find_roots(a, b, find, prec, error);
  for (int ii = 0; ii<res.size(); ii++)
    std::cout << res[ii]<< std::endl;

  return 0;
}
