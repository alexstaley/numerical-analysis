// Alex Staley #919519311
// CS451 LAB 1 -- October 2020

/*

The interval bisection method works iff 
the function is continuous and you can 
establish and initial left & right guess, 
such that:
   f(left) and f(right) have differnt signs
(i.e.: both positive or both negative).

COMPILE THIS CODE BY RUNNING:

gcc interval_bisection04_lab.c -lm

The -lm links with the math library

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f1 (double x)
{
  double y ;
  y = x*x - 2 ;
  return y ;
}


double f2 (double x)
//  three roots,
//  -3 - sqrt(3) = -4.732050,
//  -3 + sqrt(3) = -1.267949,
//   6
{
  double y ;
  y = x*x*x - 30*x - 36 ;
  return y ;
}



int interval_bisection(double (*f)(double x),
		       double left, double right,
		       double epsilon, int maxreps,
		       double results[2])
// return 0 failure, else 'numreps' (>= 1)
// 'maxreps' is the maximum iterations through the loop
{
  // Return 0 if bounds are on the same side
  // of the x-axis, or if left == right
  if (   (f(left) < 0 && f(right) < 0)
      || (f(left) > 0 && f(right) > 0)
      || (left == right)) {
    return 0;
  }

  // Normalize bounds to right > left
  if (left > right) {
    double temp = left; left = right; right = temp;
  }

  double lx, ly, rx, ry, midX, midY; //temp coords of bounds/midpoint
  int reps = 0; //number of iterations performed

  // Start temp x-bounds at given x-bounds
  lx = left;
  rx = right;

  // Binary search loop
  while (reps <= maxreps && epsilon < rx - lx) {
    // Check y-values at current x-boundaries
    ly= f(lx);
    ry= f(rx);

    // If a root is found, record it
    // and increment and return reps
    if (ly == 0 || ry == 0) {
      if (ly == 0) { results[0] = lx; }
      else         { results[0] = rx; }
      results[1] = 0;
      return reps + 1;
    }

    // Get the midpoint values
    midX = (lx + rx) / 2;
    midY = f(midX);
    results[0] = midX;
    results[1] = midY;

    // Check signs of y-values and reset x-values.
    // Increment reps and return after loop.
    if (midY < 0) {
      if (ly < 0) { lx = midX; }
      else        { rx = midX; }
    }
    else {
      if (ly < 0) { rx = midX; }
      else        { lx = midX; }
    }
    ++reps;
  }
  return reps;
}




int main()
{
  int maxreps,numr ;
  double left_guess,right_guess,res[2] ;

  // test #1:
  
  left_guess  = 1 ;
  right_guess = 2 ;

  maxreps = 100 ;
  numr = interval_bisection(f1, left_guess,right_guess,  1e-12, maxreps,  res) ;
  if (numr == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
    
    // res[0] is our approximation to a root.
    // res[1] is the function evaluated at res[0],
    // which should be close to 0 if we came close to finding a root.
    
    // NOTE: numreps equals maxreps, if the algorithm performed maxreps repititions
  }

  //////////////////////////////////////////////////////////////


  // test #2 :

  numr = interval_bisection(sin, 3,4,  1e-12, 50,  res) ;
  // for this test the function is the sin(x)
  
  if (numr == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
  }

  /////////////////////////////////////////////////////////////
  
  // test #3:
  
  printf("Enter left,right for root search : ") ;
  scanf("%lf %lf",&left_guess,&right_guess) ;

  maxreps = 100 ;
  numr = interval_bisection(f2, left_guess,right_guess,  1e-12, maxreps,  res) ;
  
  if (numr == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
  }
  
}

