/* Alex Staley -- Oct 2020
 *
 * This program solves a given system of linear
 * equations by reducing it to row echelon form
 * and then performing back-substitution.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int readFile(double m[][20]);
int rowReduce(double m[][20], int n);
void backSubstitute(double m[][20], int n);
void rowSwap(double m[][20], int cols, int a, int b);
int getMaxAbs(double m[][20], int n, int start);
void printMatrix(double m[][20], int n);



int main()
{
  double m[20][20];
  int n = readFile(m);

  if (rowReduce(m, n) < 0) {
    printf("No unique solution exists.\n\n\n");
  }
  else {
    backSubstitute(m, n);
  }

  return 0;
}



/* Read the input file
 * into a 2-d array m,
 * then print m
 */
int readFile(double m[][20]) {
  char fname[100];
  FILE *f;
  int n,r,c;

  //Find file
  printf("Enter the name of the file to read: ");
  scanf("%s", fname);
  f = fopen(fname, "r");
  if (f == NULL) {
    printf("can't read file\n");
    exit(0);
  }
  
  //Read file
  fscanf(f, "%d", &n);
  for (r=1; r<=n; ++r) {
    for (c=1; c<=n+1; ++c) {
      fscanf(f, "%lf", &m[r][c]);
    }
  }

  //Print file
  printMatrix(m, n);
  return n;
}



/* Reduce the matrix m
 * to row echelon form,
 * then print it
 */
int rowReduce(double m[][20], int n) {
  double factor;    //scalar for row addition
  int maxRow;       //row to be swapped

  for (int h=1; h<=n-1; ++h) {  //column level
    for (int k=h+1; k<=n; ++k) {  //row level

      // Check for no solution
      if (m[h][h] == 0) {
        maxRow = getMaxAbs(m, n, h);
        if (maxRow < 0) {
          printMatrix(m, n);
          return -1;
        }
        rowSwap(m, n+1, maxRow, h);
      }

      // Compute row addition factor
      // and set initial 0
      factor = (m[k][h] / m[h][h]);
      m[k][h] = 0;

      // Perform row addition
      for (int i=h+1; i<=n+1; ++i) {  //term level
        m[k][i] = m[k][i] - factor * m[h][i];
      }
    }
  }

  printMatrix(m, n);

  // Check for no solution
  if (m[n][n] == 0)
    return -1;
  return 0;
}



/* Swap two rows
 * of the matrix
 */
void rowSwap(double m[][20], int cols, int a, int b) {
  double temp[cols];
  for (int i=1; i<=cols; ++i) {
    temp[i-1] = m[a][i];
    m[a][i] = m[b][i];
    m[b][i] = temp[i-1];
  }
}



/* Return the row containing
 * the greatest absolute value
 * in a given column
 */
int getMaxAbs(double m[][20], int n, int start) {
  double max = 0;
  int row = -1; //no solution if max abs value == 0
  for (int i=start; i<=n; ++i) {
    if (fabs(m[i][start]) > max) {
      max = fabs(m[i][start]);
      row = i;
    }
  }
  return row;
}



/* Execute back substitution
 * to solve the system, and
 * then print the solution
 */
void backSubstitute(double m[][20], int n) {
  double term = 0;
  double x[n+1];
  x[n] = 0;

  // Iterate along diagonal
  for (int r=n; r>0; --r) {
    for (int c=r; c<=n; ++c) {
        term += m[r][c] * x[c];
    }

    // Solve for each row
    term = m[r][n+1] - term;
    x[r] = term / m[r][r];
    term = 0;
  }

  // Print solved equation
  for (int p=1; p<=n; ++p) {
    printf("%10.5lf  ", x[p]);
  }
  printf("\n\n") ;
}



/* Print the matrix m
 */
void printMatrix(double m[][20], int n) {
  printf("\n");
  for (int r=1; r<=n; ++r) {
    for (int c=1; c<=n+1; ++c) {
      printf("%12g", m[r][c]);
    }
    printf("\n");
  }  
  printf("\n");
}

