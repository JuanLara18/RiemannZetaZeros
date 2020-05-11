import click
from libraries.parallel_functions import finding_roots

__author__ = "Julian Jimenez-Cardenas"

@click.command()
@click.argument("a")
@click.argument("b")
@click.argument("roots", default=False)
@click.argument("cores", default=1)
@click.argument("prec", default=0.01)
@click.argument("error", default=0.001)
def main(a,b,roots,prec,error,cores):
    """
    Riemann Zeta Function Zeros Calculator.

    This program calculates how many roots are with imaginary part between [A,B] if ROOTS=False. If ROOTS = True it calculates the value of the imaginary part of these roots with a maximum error of ERROR.

    A is the lower bound of the imaginary interval (must be a float geq 0).

    B is the upper bound of the imaginary interval (must be a float geq A).

    ROOTS is a boolean that specifies if the roots are going to be calculated (default_value=False) (must be True or False).

    CORES is the number of cores that are going to be used (default=1) (must be a non-negative integer).

    PREC is the width of the intervals where the existence of the roots is going to be examined (default_value=0.01) (must be a float geq 0).

    ERROR is the maximum error in the approximation of the roots. Only works when ROOTS=True (default_value=0.001) (must be a float geq 0).

    """

    if (roots):
        roots=1
    else:
        roots=0
    res = finding_roots(float(a),float(b), roots, prec, error, cores)
    for ii in res:
        print(ii, end=" ")

if __name__ == "__main__":
    main()
