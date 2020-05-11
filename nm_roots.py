import click
from libraries.parallel_functions import call_nmroots

__author__ = "Julian Jimenez-Cardenas"

@click.command()
@click.argument("n")
@click.argument("m")
@click.argument("prec", default=0.01)
@click.argument("error", default=0.001)
def main(n,m,prec,error):
    """
    Riemann Zeta Function Zeros Calculator.

    This program calculates the set \{a_N,...,a_M\}, where a_i is the imaginary part of the i-th root with a maximum error of ERROR.

    N is the position of the first root (must be a non-negative integer).

    M is the position of the last root (must be a non-negative integer greater than N).

    PREC is the width of the intervals where the existence of the roots is going to be examined (default_value=0.01) (must be a float geq 0).

    ERROR is the maximum error in the approximation of the roots (default_value=0.001) (must be a float geq 0).

    """

    res = call_nmroots(int(n),int(m), prec, error)
    for ii in res:
        print(ii, end=" ")

if __name__ == "__main__":
    main()
