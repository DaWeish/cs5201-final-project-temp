/*
 * author Connor Walsh
 * file   QRSolver.hpp
 * brief  Implementation file for the QRSolver class
 */

#include "QRSolver.h"

template <class T>
MathVector<T> QRSolver<T>::operator()(const IMathMatrix<T>& A,
    const MathVector<T>& b) const
{
  UpTriangleMathMatrix<double> R(A.rows(), A.cols());
  MathMatrix<T> Q(A.rows(), A.cols());
  MathMatrix<T> input(A);

  QRDecomposition(input, Q, R);

  // Rx = Q^T*b
  MathMatrix<T> Qtranspose = Q.transpose();
  MathVector<T> constants = Qtranspose * b;
  MathMatrix<T> augmented = GaussianEliminationSolver<T>::augmentedMatrix
    (R, constants);

  return GaussianEliminationSolver<T>::backSubstitution(augmented);
}

template <class T>
void QRSolver<T>::QRMethod(MathMatrix<T>& A, MathMatrix<T>& Q,
    UpTriangleMathMatrix<T>& R, int numIter)
{
  for (int i = 0; i < numIter; ++i) {
    QRDecomposition(A, Q, R);

    A = ((i % 2 == 0) ?  Q * R : R * Q);
  }
}

template <class T>
void QRSolver<T>::QRDecomposition(const MathMatrix<T>& input, 
    MathMatrix<T>& orthonormal, UpTriangleMathMatrix<T>& R)
{
  MathMatrix<T> A = input.transpose();
  MathMatrix<T> Q = orthonormal.transpose();

  for (int k = 0, numRows = A.rows(); k < numRows; ++k)
  {
    for (int i = 0; i < k; ++i)
    {
      R(i, k) = A[k] * Q[i];
    }

    MathVector<T> offset(numRows);
    MathVector<T> orthagonalized(numRows);

    for (int j = 0; j < k; ++j)
    {
      offset += R(j, k) * Q[j];
    }
    orthagonalized = A[k] - offset;

    // Calculate the kth r value
    R(k, k) = orthagonalized.getMagnitude();
    if (R(k, k) == 0)
    {
      throw std::domain_error("QR method requires division by zero!");
    }

    Q[k] = (1.0 / R(k, k)) * orthagonalized;
  }

  orthonormal = Q.transpose();
}
