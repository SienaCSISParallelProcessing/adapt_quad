/*
  Adaptive quadrature

  Jim Teresco
  Williams College, Mount Holyoke College, Siena College

  Based on algorithm in Andrews (2000), Section 1.5

  Initial implementation: Wed Feb 19 22:24:24 EST 2003
*/

/* include some stuff we need */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-15

#include "timer.h"

/* count the number of function evaluations */
int counter=0;

/* the function whose integral we compute */
double f(double x) {

  counter++;
  return x*x*x + 3*x*x - 2 + sin(x*M_PI);
}

/* adaptive quadrature recursive function */

double adapt_quad(double left, double right, 
		  double f_left, double f_right,
		  double lr_area) {
  double mid = (left + right) / 2;
  double f_mid = f(mid);
  double l_area = (f_left+f_mid) * (mid-left) / 2;
  double r_area = (f_mid+f_right) * (right-mid) / 2;
  if (fabs((l_area+r_area) - lr_area) > EPSILON) {
    // recurse to integrate both halves
    l_area = adapt_quad(left, mid, f_left, f_mid, l_area);
    r_area = adapt_quad(mid, right, f_mid, f_right, r_area);
  }
  return (l_area + r_area);
}

/* The main program starts here */
int main(int argc, char *argv[]) {

  double a=0.0, b=1.0, area;
  struct timeval start, stop;

  /* we can override the default endpoints with command-line args */
  if (argc >= 3) {
    a = atof(argv[1]);
    b = atof(argv[2]);
  }

  gettimeofday(&start, NULL);

  area = adapt_quad(a, b, f(a), f(b), (f(a)+f(b))*(b-a)/2);

  gettimeofday(&stop, NULL);
  printf("Computing area %10.8f took: %f seconds, %d function evals\n", area, 
	 diffgettime(start,stop), counter);

  return 0;
}
