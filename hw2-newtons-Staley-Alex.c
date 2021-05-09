/* Alex Staley -- Oct 2020
 *
 * This program uses Newton's method
 * and synthetic division to calculate
 * all the real and complex roots
 * of an arbitrary polynomial.
 *
 * The user may input the degree and
 * coefficients of the polynomial
 * via the command line. If they do not,
 * they will be prompted to enter
 * these values upon starting the program.
 *
 * Expected input:
 *      degree, n term, n-1 term, n-2 term, ..., 2 term, 1 term, 0 term
 * For example, to generate the polynomial
 *      2x^4 + 5x^3 - 6x + 10 = 0
 * the user should run the script
 *      ./a.out 4 2 5 0 -6 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <time.h>

void newtonsMeth(complex poly[], complex roots[], int deg);
complex synthDivide(complex guess, complex full[], complex defl[], int deg);

int getPolynomial(complex poly[]);
void printPolynomial(complex poly[], int deg);
void printRoots(complex roots[], int deg);



int main(int argc, char* argv[])
{
    int deg, i, j;
    srand48(time(NULL));

    // Read polynomial
    complex poly[100];
    if (argc < 2) {  //from prompt
        deg = getPolynomial(poly);
    }
    else {  //from command line
        deg = atoi(argv[1]);
        i=2;
        for (j=deg; j>=0; --j) {
            poly[j] = atoi(argv[i++]) + 0*I;
        }
        printPolynomial(poly, deg);
    }

    // Find roots
    complex roots[deg];
    newtonsMeth(poly, roots, deg);

    // Print roots
    printRoots(roots, deg);

    return 0;
}



/* Use Newton's method to find the real
 * and complex roots of a given polynomial
 */
void newtonsMeth(complex poly[], complex roots[], int deg) {
    complex x, numtor, dentor;  //NM: x = x - numtor/dentor
    complex deriv[100];         //derived polynomial coefficients
    complex temp[100];          //placeholder

    int degrees = deg;

    for (int i=0; i<degrees; ++i) {
        // Generate a guess
        x = drand48() + drand48()*I;

        // Use Newton's Method to find a root
        for (int j=0; j<50; ++j) {
            numtor = synthDivide(x, poly, deriv, deg);
            dentor = synthDivide(x, deriv, temp, deg-1);
            x = x - numtor / dentor;
        }

        // Copy and deflate the polynomial
        for (int k=0; k<=deg; ++k) {
            temp[k] = poly[k];
        }
        synthDivide(x, temp, poly, deg);

        // Record the root and decrement
        // the degree of the polynomial
        roots[i] = x;
        --deg;
    }
}


/* Perform synthetic division on the
 * polynomial at a given complex x-value
 */
complex synthDivide(complex guess, complex full[], complex defl[], int deg) {
    complex result;

    // Execute synthetic division
    defl[deg] = full[deg];
    for (int i=deg-1; i>=0; --i) {
        defl[i] = guess * defl[i+1] + full[i];
    }

    // Record the result and shift
    // the deflated polynomial
    result = defl[0];
    for (int j=0; j<deg; ++j) {
        defl[j] = defl[j+1];
    }

    return result;
}


/* Read in the polynomial's degree
 * and coefficients from the user
 */
int getPolynomial(complex poly[]) {
    double coef;
    int deg;

    // Get degree
    printf("Enter degree\n");
    scanf("%d", &deg);

    // Get coefficients
    printf("Enter coefficients, ");
    printf("starting with higher-order terms\n");
    for (int i=deg; i>=0; --i) {
        scanf("%lf", &coef);
        poly[i] = coef + 0*I;
    }

    // Print the polynomial
    printPolynomial(poly, deg);
    return deg;
}


/* Pleasantly display the given polynomial
 */
void printPolynomial(complex poly[], int deg) {
    printf("\nYour polynomial is\t");

    // Print higher-order terms
    for (int j=deg; j>1; --j) {
        if (creal(poly[j]) != 0) {  //if coefficient == 0, omit term
            if (creal(poly[j]) != 1) {  //if coefficient == 1, omit coefficient
                printf("%g", creal(poly[j]));
            }
            printf("x^%d + ", j);
        }
    }

    // Print linear term
    if (deg > 0) {
        if (creal(poly[1]) != 0) {  //if coefficient == 0, omit term
            if (creal(poly[1]) != 1) {  //if coefficient == 1, omit coefficient
                printf("%g", creal(poly[1]));
            }
            printf("x");
            if (creal(poly[0] != 0)) {  //if constant term == 0, omit final '+'
                printf(" + ");
            }
        }
    }

    // Print constant term
    if (creal(poly[0]) != 0) {
        printf("%g", creal(poly[0]));
    }
    printf(" = 0\n");
}


/* Pleasantly display the roots
 * found by Newton's method
 */
void printRoots(complex roots[], int deg) {
    printf("\nFound %d root", deg);
    if (deg != 1) printf("s");  //can't help it
    if (deg != 0) printf(":\n");

    for (int i=0; i<deg; ++i) {
        printf("%20.16lf + %20.16lf*I\n", creal(roots[i]), cimag(roots[i]));
    }
    printf("\n");
}

