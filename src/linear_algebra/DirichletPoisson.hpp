/*
 * Connor Walsh
 * DirichletPoisson.hpp : Implementation file for DirichletPoisson class
 */

#include "DirichletPoisson.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"

template <class T>
int DirichletPoisson<T>::getPointOffset(int x, int y) const
{
  return (x - 1) + ((y - 1) * (numDivs - 1));
}

/*
 * pre: IMathMatrix should be square with size (numDivs - 1)^2
 */
template <class T>
template <T fnLow(T), T fnHigh(T), T fnLeft(T), T fnRight(T), T fnForce(T, T)>
void DirichletPoisson<T>::generate(IMathMatrix<T>& A, MathVector<T>& b) const
{
  int xdir, ydir;
  T h = length / numDivs;
  for (int x = 1; x < numDivs; ++x)
  {
    for (int y = 1; y < numDivs; ++y)
    {
      int pointOffset = getPointOffset(x, y);
      A(pointOffset, pointOffset) = 1;

      // Check the left direction point
      xdir = x - 1;
      ydir = y;
      if (xdir == 0)
      {
        // Update the b for the current point
        b[pointOffset] += 0.25*(fnLeft(yLow + ydir*h));
      }
      else
      {
        // Update A at [currentpoint][directionPoint] = -1/4
        A(pointOffset, getPointOffset(xdir, ydir)) = -0.25;
      }

      // Check the right direction point
      xdir = x + 1;
      if (xdir == numDivs)
      {
        // Update the b for the current point
        b[pointOffset] += 0.25*(fnRight(yLow + ydir*h));
      }
      else
      {
        A(pointOffset, getPointOffset(xdir, ydir)) = -0.25;
      }
      
      // Check the up direction point
      xdir = x;
      ydir = y + 1;
      if (ydir == numDivs)
      {
        b[pointOffset] += 0.25*(fnHigh(xLow + xdir*h));
      }
      else
      {
        A(pointOffset, getPointOffset(xdir, ydir)) = -0.25;
      }

      // Check the down direction point
      ydir = y - 1;
      if (ydir == 0)
      {
        b[pointOffset] += 0.25*(fnLow(xLow + xdir*h));
      }
      else
      {
        A(pointOffset, getPointOffset(xdir, ydir)) = -0.25;
      }

      // Subtract the forcing function from b
      b[pointOffset] -= ((h*h)*(fnForce(xLow + x*h, yLow + y*h)))/4.0;
    }
  }
}

template <class T>
template <T fnLow(T), T fnHigh(T), T fnLeft(T), T fnRight(T), T fnForce(T, T)>
MathVector<T> DirichletPoisson<T>::getSolution(int numDivisions)
{
  numDivs = numDivisions;
  int dimensions = (numDivs - 1)*(numDivs - 1);

  MathMatrix<T> A(dimensions, dimensions);
  MathVector<T> b(dimensions);

  generate<fnLow, fnHigh, fnLeft, fnRight, fnForce>(A, b);

  return mySolver(A, b);
}

template <class T>
template <T solution(T, T)>
MathVector<T> DirichletPoisson<T>::getActualSolution(int numDivisions)
{
  MathVector<T> result((numDivisions - 1)*(numDivisions - 1));
  T h = length / numDivs;
  for (int x = 1; x < numDivisions; ++x)
  {
    for (int y = 1; y < numDivisions; ++y)
    {
      int pointOffset = getPointOffset(x, y);

      result[pointOffset] = solution(xLow + x*h, yLow + y*h);
    }
  }

  return result;
}
