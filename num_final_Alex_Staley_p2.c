/*
 * Alex Staley -- 919519311
 * CS451 Final -- Problem 2
 * December 2020
 *
 * This program accepts a number of coordinates
 * input via .txt file or clicked by the user,
 * and creates the best-fit quadratic curve
 * that passes through the given endpoints.
 *
 * Prototypes for added functions can be found
 * on lines 22-24. All other added source code
 * (including the implementation of these functions)
 * lives below line 131.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FPToolkit.c"

double getSlope(double p[], double q[], int n);
double getLine(double p[], double q[], double slope, int x);
double getError(double p[], double q[], int n, double s);



int click_and_save(double p[], double q[])
{
  double xy[2] ;
  int numpoints ;

  G_rgb(1, 0, 0) ; 
  G_fill_rectangle(0,0,  20,10) ;

  numpoints = 0 ;
  while (0 == 0) {

     G_wait_click(xy) ;

     if ((xy[0] >= 0) && (xy[0] <= 20) && 
         (xy[1] >= 0) && (xy[1] <= 10))  { break ; }

     G_rgb(1, 1, 0) ; 
     G_circle(xy[0], xy[1], 3) ;     

     p[numpoints] = xy[0] ; q[numpoints] = xy[1] ;

     if (numpoints > 0) {
       G_line (p[numpoints-1],q[numpoints-1], p[numpoints],q[numpoints]) ;
     }

     numpoints++ ;

  }

  return numpoints ;
}




int input_knots(double p[], double q[])
{
  char fname[200] ;
  FILE *f ;
  int n,i ;
  
  printf("Enter filename to input knots from :  ") ;
  scanf("%s",fname) ;
  f = fopen(fname,"r") ;
  if (f == NULL) {
    printf("can't open file, %s\n", fname) ;
    return 0 ;
  }
  fscanf(f,"%d\n",&n) ;
  for (i = 0 ; i <= n ; i++) {  // n is index of last knot
    fscanf(f,"%lf  %lf\n", &p[i], &q[i]) ;
  }
  fclose(f) ;
  return n ;
}




int main()
{
  int choice ;
  double p[1000],q[1000] ;
  int n ;

  //G_choose_repl_display() ; // comment this out if not using repl
  
  printf("Enter 0 to click knots, else get knots from an existing file : ") ;
  scanf("%d", &choice) ;

  if (choice == 0) {

    printf("\n") ;
    printf("Click points, left to right.\n") ;
    G_init_graphics (600,600) ;
    G_rgb(0,0,0) ;
    G_clear() ;
    
    n = click_and_save(p,q) ;
    n = n - 1; // so q[n] is the last item

  } else {

    n = input_knots(p,q) ; // n is index of last knot
    
    G_init_graphics (600,600) ;
    G_rgb(0,0,0) ;
    G_clear() ;

  }


  G_rgb(0,0,0) ;
  G_clear() ;

  int k ;
  G_rgb(0,1,0) ;
  for (k = 0 ; k <= n ; k++) {
    G_circle(p[k],q[k],2) ;
  }
  

  
  // your code goes here :  

  double y,A,s;
  s = getSlope(p,q,n);
  A = getError(p,q,n,s);

  G_rgb(1,0,0);
  for (int i=0; i<600; ++i) {
    y = getLine(p,q,s, i) + A*(i-p[0])*(i-p[n]);
    G_point(i,y);
  }

  int key = G_wait_key() ;
}

/*
 * Get the slope of the line intersecting
 * the points (p[0], q[0]) and (p[n], q[n])
 */
double getSlope(double p[], double q[], int n) {
  if (p[n] == p[0]) return INFINITY;
  return (q[n]-q[0]) / (p[n]-p[0]);
}

/*
 * Given an x-coordinate, return the corresponding
 * y-coordinate on the line intersecting
 * the points (p[0], q[0]) and (p[n], q[n])
 */
double getLine(double p[], double q[], double slope, int x) {
  return q[0] + slope*(x-p[0]);
}

/*
 * Return the "A" term required to minimize the
 * total square vertical error between the points
 * (p[i], q[i]) and the best-fit quadratic curve
 * Q(x) = L(x) + A * (x-p[0]) * (x-p[n])
 */
double getError(double p[], double q[], int n, double s) {
  double numtor = 0;
  double dentor = 0;

  for (int i=0; i<n; ++i) {
    numtor += q[i] - getLine(p,q,s, p[i]);
    dentor += (p[i]-p[0]) * (p[i]-p[n]);
  }

  if (dentor == 0) return INFINITY;
  return numtor/dentor;
}

