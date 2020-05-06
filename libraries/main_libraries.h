#include <complex>
#include <cmath>
#include <boost/math/special_functions/bernoulli.hpp>

using namespace std::complex_literals;

std::complex<double> semi_factorial(std::complex<double> a,
  int b){
  /* This function calculates a*(a+1)*(a+2)*...*(a+b)
  Input:
    - a: Complex Number.
    - b: integer.
  Output:
    - res: Complex Number.
   */
  std::complex<double> res = 1;
  for (int ii=0; ii<(b+1); ii++){
    std::complex<double> mult(real(a)+ii, imag(a));
    res = res*mult;
  }
  return res;
}

std::vector<float> bernoulli_numbers(int n){
  /* This function calculates the first n even Bernoulli numbers.
  Input:
    - n: integer
  Output:
    - res: vector
  */
  std::vector<float> res;
  boost::math::bernoulli_b2n<float>(0, n, std::back_inserter(res));
  return res;
}
