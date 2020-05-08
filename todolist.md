# To Do List

- [ ] Studies.
   - [x] Study the ways of determine the roots over the critical line (**Edwards H.M. Riemann Zeta Function* page 119...).
   - [ ] Get the way to parallelize the program using KUDA (maybe...).

 - [ ] Program.

    - [ ] Implement the way to determine how many roots and which are in a given interval.

       - [ ] Implement in C++ the calculation of this.

         - [x] Implement the function `semi_factorial`, which calculates the value
           $$
           a\times(a+1)\times\cdots\times (a+b), \text{ for } a\in\mathbb{C} \text{ and }b\in\mathbb{N}.
           $$

         - [x] Implement a function to find the Bernoulli numbers.

           - For this I used a library called boost. You can get it through https://www.boost.org/users/download/. To compile a script using this library use 

             ```bash
             g++ -I boost_1_73_0/ test.cpp -o name
             ```

             having in mind that the library *boost_1_73_0/* is in the same place than the file that you are compiling. *test.cpp* and *name* must be replaced depending of the case.

         - [x] Implement a function to approximate the Riemann Zeta Function using the Euler's Summation Formula.

           - [x] Design an intelligent condition to get the N value given the parameter s to avoid failures in the approximation.
       
         - [x] Construct the function theta that appears in the complex exponential to determine the sign of Z(t).
       
         - [x] Construct the function Z(t).
       
         - [x] Construct the function to find the number of roots in a given interval [a,b].
       
         - [x] Construct the function to find the exact value of the roots in a given interval [a,b] (this has become the same function than the last one).
       
         - [x] Construct a function that finds the n-th root. In fact, the function nm_roots return from the n-th root to the m-th root.
       
       - [ ] Improvement of parts of the code.
       
          - [ ] In the function number_roots, if one knows what is the minimum distance between two roots, the code can be improved changing the *prec* parameter.
       
       - [ ] Implement in Python the way of interacting with the user.
       
       - [ ] Parallelize the way of finding the roots in a given interval. Maybe you should divide the interval in n parts, where n is the number of dedicated nuclei.

 - [ ] Readme.

    - [ ] Installation of required libraries.
       - [x] Construct the documentation to explain how to install boost.
    - [ ] Explain how to make the program works.



