/*
 * author Connor Walsh
 * file   QRSolver.h
 * brief  This class implements the Matrix Solver interface using the QR method
 */

#ifndef QR_SOLVER_H
#define QR_SOLVER_H

#include <vector>
#include <stdexcept>
#include <iostream>

#include "IMatrixSolver.h"
#include "../MathVector.h"
#include "../math_matrix/IMathMatrix.h"
#include "../math_matrix/MathMatrix.h"
#include "../math_matrix/UpTriangleMathMatrix.h"
#include "../math_matrix/LowTriangleMathMatrix.h"

////////////////////////////////////////////////////////////////////////////////
// class QRDecompositor
// brief this Functor runs the QR Decomposition algorithm on the passed in
//    linearly independent vectors and returns the set of orthonormal vectors
//    and their multipliers
////////////////////////////////////////////////////////////////////////////////
template <class T>
class QRSolver : public IMatrixSolver<T>
{
  private:
    void QRMethod(MathMatrix<T>& A, MathMatrix<T>& Q, 
        UpTriangleMathMatrix<T>& R, int numIter) const;
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
    virtual MathVector<T> operator()
      (const IMathMatrix<T>& A, const MathVector<T>& b) const;
};

template <class T>
MathVector<T> QRSolver<T>::operator()(const IMathMatrix<T>& A,
    const MathVector<T>& b) const
{
  // TODO implement this function body
}

// TODO fix this function to work with MathMatrix correctly
template <class T>
void QRSolver<T>::QRMethod(MathMatrix<T>& A, MathMatrix<T>& Q,
    UpTriangleMathMatrix<T>& R, int numIter) const
{
  for (int a = 0; a < numIter; ++a) {
    for (int k = 0, numRows = A.rows(); k < numRows; ++k)
    {
      for (int i = 0; i < k; ++i)
      {
        R(k, i) = (A)[k] * (Q)[i];
      }

      MathVector<T> offset(numRows);
      MathVector<T> orthagonalized(numRows);

      for (int j = 0; j < k; ++j)
      {
        offset += R(k, j) * (Q)[j];
      }
      orthagonalized = (A)[k] - offset;

      // Calculate the kth r value
      (R)(k, k) = orthagonalized.getMagnitude();
      if ((R)(k, k) == 0)
      {
        throw std::domain_error("QR method requires division by zero!");
      }

      (Q)[k] = (1.0 / (R)(k, k)) * orthagonalized;
    }
    A = ((a % 2 == 0) ?  Q * R : R * Q);
  }
}

#endif
