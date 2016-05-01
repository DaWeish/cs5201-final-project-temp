////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   QRCompositor.h
// brief  Simple Functor to implement the QR Decomposition algorithm 
////////////////////////////////////////////////////////////////////////////////

#ifndef QRDECOMPOSITION_H
#define QRDECOMPOSITION_H

#include <vector>
#include <stdexcept>
#include <iostream>

#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/math_matrix/IMathMatrix.h"

////////////////////////////////////////////////////////////////////////////////
// class QRDecompositor
// brief this Functor runs the QR Decomposition algorithm on the passed in
//    linearly independent vectors and returns the set of orthonormal vectors
//    and their multipliers
////////////////////////////////////////////////////////////////////////////////
template <class T>
class QRDecompositor
{
////////////////////////////////////////////////////////////////////////////////
// fn operator()
// brief This operator runs the QR Decomposition algorithm
// pre input must contain a set of n vectors each with length n. orthonormal must
// contain a set of n vectors each with length n. triangle must contain a set of
// n vectors each with length n and initialized to zero.
// post orthonormal now contains the set of orthonormal vectors built from input.
// triangle contains a triangle matrix of the multiplier values. This is true as
// long as division by zero does not occur, otherwise an exception is thrown.
////////////////////////////////////////////////////////////////////////////////
  public:
    void operator()(IMathMatrix<T>* input, IMathMatrix<T>* orthonormal,
        IMathMatrix<T>* triangle, int numIter) const;
};

template <class T>
void QRDecompositor<T>::operator()(IMathMatrix<T>* input, IMathMatrix<T>* 
    orthonormal, IMathMatrix<T>* triangle, int numIter) const
{
  for (int a = 0; a < numIter; ++a) {
    for (int k = 0, numRows = input->rows(); k < numRows; ++k)
    {
      for (int i = 0; i < k; ++i)
      {
        (*triangle)(k, i) = (*input)[k] * (*orthonormal)[i];
      }

      MathVector<T> offset(numRows);
      MathVector<T> orthagonalized(numRows);

      for (int j = 0; j < k; ++j)
      {
        offset += (*triangle)(k, j) * (*orthonormal)[j];
      }
      orthagonalized = (*input)[k] - offset;

      // Calculate the kth r value
      (*triangle)(k, k) = orthagonalized.getMagnitude();
      if ((*triangle)(k, k) == 0)
      {
        throw std::domain_error("QR method requires division by zero!");
      }

      (*orthonormal)[k] = (1.0 / (*triangle)(k, k)) * orthagonalized;
    }
    delete input;
    (a % 2 == 0) ?  input = (*orthonormal) * (*triangle) :
    input = (*triangle) * (*orthonormal);
  }
}
#endif
