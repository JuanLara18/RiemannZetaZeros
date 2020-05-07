#include <complex>
#include <cmath>
#include <iostream>
#include <boost/math/special_functions/bernoulli.hpp>

using namespace std::complex_literals;
const double PI = std::atan(1.0)*4;

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

std::complex<double> riemann_zeta(std::complex<double> s, int nu = 8){
  /* This function calculates the value of the Riemann Zeta Function in s,
  using the parameters N and nu for the approximation of the Euler's Summation
  Method.
  Input:
    - s: complex number.
    - nu: integer.
  Output:
    - zeta: complex number.
  */
  int N;
  // Empiric bound
  if (abs(s)<50){
    N = 1000;
  }
  else{
    N = abs(s)/4;
  }
  std::complex<double> zeta(0, 0);

  for (int ii =1; ii<N; ii++){
    zeta = zeta + pow(ii, -s);
  }
  zeta = zeta + pow(N, std::complex<double>(1.,0)-s)/(s-std::complex<double>(1.,0))
  +pow(N,-s)/std::complex<double>(2.,0);

  std::vector<float> bn = bernoulli_numbers(nu+1);
  for (int ii = 1; ii<(nu+1); ii++){
    zeta = zeta + std::complex<double>(bn[ii],0)*semi_factorial(s,2*(ii-1))*
    pow(N, -s-std::complex<double>(2*ii-1,0))/semi_factorial(std::complex<double>(1.,0), 2*ii-1);
  }
  // This is the error in the approximation
  double error = abs(semi_factorial(s,2*nu-1)*std::complex<double>(bn[nu],0)*
  pow(N,-real(s)-2*nu+1)/semi_factorial(std::complex<double>(1,0),2*nu-1)/(real(s)+2*nu-1));
  if (error >1){
      std::cout << "Warning: the bound for the error is "<<error<<" which means"
      <<" that the precission of these calculations is inadequate. You could try to"
      << " change N and nu of the riemann_zeta function" <<std::endl;
  }
  return zeta;
}

std::complex<double> theta(double t){
  /* This function calculates e^{i*theta(t)}, needed to find the sign of the
  function Z(t), that is required to identify the zeros of the zeta riemann
  function.

  The error of this approximation is at most 64/(63t^5)
  Input:
    - t: double.
  Output:
    - result: complex number.
  */
  double tmp = (t*std::log(t/2/PI)/2.-t/2-PI/8+1/48./t+7./5760./pow(t,3));
  std::complex<double> result(cos(tmp),sin(tmp));
  return result;
}

int sign_Z(double t){
  /* This is the Z function, that receives a double t as argument. The sign of
  this function is the opposite sign of xi(1/2+it) (Riemann Zeta Function removing
  all the poles).
  Input:
    - t: double.
  Output:
    - sign: -1,1,0 (integer).
  */
  std::complex<double> temporal = theta(t)*riemann_zeta(std::complex<double>(1/2.,t));
  double real_part = std::real(temporal);
  int sign;
  if (real_part == 0){
    sign = 0;
  }
  else{
    sign = real_part/abs(real_part);
  }
  return sign;
}
