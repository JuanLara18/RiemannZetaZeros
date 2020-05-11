# Calculation of the Zeros of the Riemann Zeta Function

This program can calculate the number of non-trivial roots of the Riemann Zeta Function for a given imaginary interval [a,b] and show an explicit list of which they are. It can also show a list with the imaginary part from the n-th root to the m-th root.

## Installation

To get the repository type in a terminal

```bash
git clone https://github.com/julian20250/Practice.git
```

### Needed Libraries

- Boost.

  In order to calculate the Bernoulli numbers, this library is needed. To install it, download the last version https://www.boost.org/users/download/ and unpack its contents in the **libraries/** directory of this project.
  
- Click.

  To execute the programs you need `click`. It can be easily installed with pip.

  ```bash
  pip install click
  ```

## Usage 

There are two main scripts: `find_roots.py` and `nm_roots.py`. The documentation of each one can be accessed writing

```bash
python find_roots.py --help
```

or

```bash
python nm_roots.py --help
```

 `find_roots.py` finds the number of roots with imaginary part in a given interval [a,b] and `nm_roots.py` prints a list with the imaginary part from the n-th root to the m-th root. The first script can be parallelized in order to increase the execution speed. For more information refer to the documentation of each script.

