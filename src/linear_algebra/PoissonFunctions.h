/*
 * Connor Walsh
 * PoissonFunctions.h : Set of functions for use with the Final Homework Problem
 */

double forcingFunction(double x, double y)
{
  return -2*(x*x + y*y);
}

double leftBound(double y)
{
  return 1+(y*y);
}

double rightBound(double y)
{
  return y*0;
}

double upperBound(double x)
{
  return 2*(1-x*x);
}

double lowerBound(double x)
{
  return 1-x*x;
}

double Solution(double x, double y)
{
  return (1-x*x)*(1+y*y);
}
