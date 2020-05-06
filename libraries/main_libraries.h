#include <complex>
#include <cmath>

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
