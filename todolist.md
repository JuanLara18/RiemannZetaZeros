# To Do List

- [x] Studies.
   - [x] Study the ways of determine the roots over the critical line (**Edwards H.M. Riemann Zeta Function* page 119...).
   - [x] Get the way to parallelize the program using KUDA (maybe...). I actually made the parallelization using Python.

 - [ ] Program.

    - [ ] Implement the way to determine how many roots and which are in a given interval.

       - [x] Implement in C++ the calculation of this.

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

       - [x] Implement in Python the way of interacting with the user.

          - [x] Read the documentation of `npyscreen` in order to make the graphical interface of the program.

             I dediced that this library is not adequate because of its lack of documentation.

          - [x] Read the documentation of `kivy` in order to make the graphical interface of the program.

            You have to install xclip. `sudo apt-get install xclip`.

          - [x] I think that the `kivy` interface is not as good as I thought, because it gets lagged and exploits when the program takes so long, so I will make a simple interface in the terminal.

          - [x] Construct a simple way to interact with the user using `click`.

          - [x] Communicate the graphical interface to the `main_libraries.py` script.

            - [x] Implement finding_roots in the graphical interface.
              - [x] Save the output of this function in a .txt.
            - [x] Create a new function in  `parallel_functions.py` to execute in the graphical interface the method from c++ dedicated to find from the n-th root to the n-th root.

       - [x] Parallelize the way of finding the roots in a given interval. Maybe you should divide the interval in n parts, where n is the number of dedicated nuclei.

       - [ ] Try to improve the parallelization, because the last cores (the ones that are farther from zero) take more time than the nearer ones.

 - [ ] Readme.

    - [ ] Installation of required libraries.
       - [x] Construct the documentation to explain how to install boost.
       - [x] Construct the documentation to explain how to install kivy (unneeded).
       - [x] Construct the documentation to explain how to install xclip (unneeded).
       - [x] Construct the documentation to install `click`.
    - [ ] Explain how to make the program works.
       - [ ] Explain the mathematics behind this program (maybe in a pdf).
       - [ ] Explain how to use the program.
          - [x] Write the documentation of the program.
          - [ ] Wait for some beta testers to tell you some improvements.



