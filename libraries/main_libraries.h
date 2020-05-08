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

int get_sign(double t){
  /* This function calculates the sign of t.
  Input:
    - t: double.
  Output:
    - sign: -1,1,0 (integer).

  */
  int sign;
  if (t == 0.0){
    sign = 0;
  }
  else{
    sign = t/abs(t);
  }
  return sign;
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
  std::complex<double> temporal = theta(1.*t)*riemann_zeta(std::complex<double>(1/2.,1.*t));
  double real_part = std::real(temporal);
  //std::cout << get_sign(real_part) << std::endl;
  return get_sign(real_part);
}

double bisection(double a, double b, double error){
  /* This function finds the exact imaginary part of the root in the interval
  (a,b), with a maximum error given by the variable error.
  Input:
    - a: double.
    - b: double.
    - error: double.
  Output:
    - root: double.
  */
  double point1 = a;
  double point2 = (a+b)/2;
  double point3 = b;

  while (((point2-point1) >error) && ((point3 - point2) > error)) {
    if (sign_Z(point1) != sign_Z(point2)){
      point3 = point2;
      point2 = (point1+point2)/2;
    }else{
      point1 = point2;
      point2 = (point2+point3)/2;
    }
  }
  return point2;
}

std::vector<float> find_roots(double a, double b, bool find = 0,
  double prec = 0.01, double error = 0.001){
  /* This function tries to find the roots in the interval [a,b] using a given
  precission prec. If the roots are nearer than prec, the function will have
  problems to find them.

  There are two possible functions for this method. if find = 0, this
  function is going to calculate how many roots are in the interval, and if
  find_ = 1, the method is going to find explicitly the roots via bisection
  with precission error.

  Input:
    - a: double.
    - b: double.
    - find: bool (default = 0).
    - prec: double (default = 0.01).
    - error: double (default =0.01).
  Output:
    - result: vector (with 1 component if find=0, and n+1 components if find=1,
              where the first component is the number of roots and the following
              components are the imaginary part of all roots found).
  */
  std::vector<float> result;
  result.push_back(0);

  if (a == 0.0){
    a = 0.1;
  }
  int steps = (b-a)/prec;
  if (((b-a)/prec - steps) != 0.0){
    steps++;
  }
  steps++;
  int last_sign = sign_Z(a);
  if (last_sign == 0){
    result[0]++;
    if (find){
      result.push_back(a);
    }
  }
  int tmp_sign;
  for(int ii = 1; ii<(steps-1); ii++){
    tmp_sign = sign_Z(a + ii*prec);
    if (tmp_sign == 0){
      result[0]++;
      if (find){
        result.push_back(a + ii*prec);
      }
    }
    if ((last_sign != tmp_sign) && (tmp_sign != 0) && (last_sign != 0)){
      result[0]++;
      if (find){
        result.push_back(bisection(a + (ii-1)*prec, a + ii*prec, error));
      }
    }
    last_sign = tmp_sign;
  }
  tmp_sign = sign_Z(b);
  if (tmp_sign == 0){
    result[0]++;
    if (find){
      result.push_back(b);
    }
  }
  if ((last_sign != tmp_sign) && (tmp_sign != 0) && (last_sign != 0)){
    result[0]++;
    if (find){
      result.push_back(bisection(a + (steps-2)*prec,b,error));
    }
  }
  return result;
}
