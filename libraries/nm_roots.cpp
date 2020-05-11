#include "main_libraries.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

int main(int argc, char **argv){
  int n = std::atoi(argv[1]);
  int m = std::atoi(argv[2]);
  double prec = std::strtod(argv[3], NULL);
  double error = std::strtod(argv[4], NULL);

  std::vector<float> res = nm_roots(n, m, prec, error);
  for (int ii = 0; ii<res.size(); ii++)
    std::cout << res[ii]<< std::endl;

  return 0;
}
