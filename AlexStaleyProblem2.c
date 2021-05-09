/* Alex Staley -- Nov 2020
 *
 * CS451 Midterm -- Problem 2
 *
 * This program solves a given system of linear
 * equations that has a decreasing number
 * of active coefficients in O(n^2) time.
 *
 * The algorithm makes use of the commutativity
 * of addition: 2x + 3y + 5z = 20 can be
 * rewritten as 5z + 3y + 2x = 20.
 *
 * So the prescribed file input format
 * represents a system of equations that
 * can be reinterpreted into row-echelon
 * format at no increased time complexity.
 *
 * 1  2  3  4  | a          4  3  2  1  | a
 * 5  6  7     | b    ==       7  6  5  | b
 * 8  9        | c                9  8  | c
 * 10          | d                   10 | d
 *
 * Back-substitution is performed on the
 * resulting row-echelon matrix in O(n^2) time.
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXN 21

int readFile(double m[][MAXN]);
void backSubstitute(double m[][MAXN], int n, double x[]);
void printSolutions(double x[], int n);



int main()
{
  double matrix[MAXN][MAXN];
  double solutions[MAXN];

  int numEqs = readFile(matrix);
  backSubstitute(matrix, numEqs, solutions);
  printSolutions(solutions, numEqs);

  return 0;
}



/* Read the input file into a
 * row-echelon matrix in O(n^2) time.
 * Return the number of equations.
 *   m = matrix
 */
int readFile(double m[][MAXN]) {
  char fname[100];
  FILE *f;
  int n;

  // Get the filename
  printf("Enter the name of the file to read: ");
  scanf("%s", fname);
  f = fopen(fname, "r");
  if (f == NULL) {
    printf(“Can't read file.\n”);
    exit(0);
  }
  
  // Check the number of equations
  fscanf(f, "%d", &n);
  if (n >= MAXN) {
    printf("Maximum %d equations... ", MAXN-1);
    printf("the file '%s' has %d.\n", fname, n);
    exit(0);
  }

  // Read the file as a matrix
  // in row-echelon form
  for (int r=1; r<=n; ++r) {
    for (int c=n; c>=r; --c) {
      fscanf(f, "%lf", &m[r][c]);
    }
    fscanf(f, "%lf", &m[r][n+1]);
  }
  return n;
}



/* Execute back-substitution to
 * solve the system in O(n^2) time.
 *   m = matrix
 *   n = number of equations
 *   x = array of solutions
 */
void backSubstitute(double m[][MAXN], int n, double x[]) {
  double term = 0;

  // Iterate along diagonal
  for (int r=n; r>0; --r) {
    for (int c=n; c>r; --c) {
      term += m[r][c] * x[c];
    }

    // Solve for each row
    term = m[r][n+1] - term;
    x[r] = term / m[r][r];
    term = 0;
  }
}



/* Print the solutions in
 * proper (i.e. reverse) order:
 * sol.1 = x[n]   sol.2 = x[n-1] ... sol.n = x[1]
 *   x = array of solutions
 *   n = number of equations
 */
void printSolutions(double x[], int n) {
  printf("\n\n");
  for (int p=n; p>=1; --p) {
    printf("x%d = %g   ", n-p+1, x[p]);
  }
  printf("\n\n");
}

