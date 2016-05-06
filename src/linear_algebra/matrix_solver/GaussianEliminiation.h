/*
 * author Connor Walsh
 * file   GaussianEliminationSolver.h
 * brief  Class which implements the IMatrixSolver interface using Gaussian
 *        Elimination
 */

#ifndef GAUSSIAN_ELIMINATION_SOLVER_H
#define GAUSSIAN_ELIMINATION_SOLVER_H

#pragma once

#include <stdexcept>

#include "IMatrixSolver.h"
#include "../MathVector.h"
#include "../math_matrix/IMathMatrix.h"
#include "../math_matrix/MathMatrix.h"

////////////////////////////////////////////////////////////////////////////////
// class GaussianElimination
// brief This class implements a functor for performing Gaussian Elimination
////////////////////////////////////////////////////////////////////////////////
template <class T>
class GaussianElimination : public IMatrixSolver<T>
{
  bool usePivot = false;

  private:
    ////////////////////////////////////////////////////////////////////////////
    // fn getMaxColumnValueRow
    // brief This function is used during pivoting to get the row index which
    //    is to be pivoted with the current row
    ////////////////////////////////////////////////////////////////////////////
    static int getMaxColumnValueRow(const IMathMatrix<T>& matrix, int column,
        int startRow);

  public:
    ////////////////////////////////////////////////////////////////////////////
    // fn operator()
    // brief This function operator performs the Gaussian elimination on a 
    //    given Matrix and constants. Can also perform partial pivoting
    // pre coefficients and constants must be of compatible dimensions
    // post returns the vector x in Ax = b where A = coefficients and
    //    b = constants
    ////////////////////////////////////////////////////////////////////////////
    virtual MathVector<T> operator()
      (const IMathMatrix<T>& A, const MathVector<T>& b) const;

    ////////////////////////////////////////////////////////////////////////////
    // fn augmentedMatrix
    // brief This function creates an augmented matrix from a set of coefficients
    //    and a constants MathVector
    // pre  constants' size must be equal to coefficients.rows()
    // post returns a matrix of size coefficients.rows() x 
    //    coefficients.columns() + 1 that is an augmented matrix of the inputs
    ////////////////////////////////////////////////////////////////////////////
    static MathMatrix<T> augmentedMatrix(const IMathMatrix<T>& coefficients,
        const MathVector<T>& constants);

    ////////////////////////////////////////////////////////////////////////////
    // fn forwardElimination
    // brief Performs Gaussian forward elimination in place on an augmented
    //    MathMatrix2D
    // pre augmented must be a matrix that is of format created by
    //    member function augmentedMatrix
    // post returns a new augmented matrix that is in eschelon form with the
    //    multipliers in the zero places
    ////////////////////////////////////////////////////////////////////////////
    static MathMatrix<T> forwardElimination(const IMathMatrix<T>& augmented,
        bool usePartialPivot = false);

    ////////////////////////////////////////////////////////////////////////////
    // fn backSubstitution
    // brief Retrives the values represented by the forward elminiation matrix
    // pre augmented is in echelon form
    // post returns a new matrix where the rightmost column values are replaced
    //    with the solutions to the equation Ax=b represented by augmented
    ////////////////////////////////////////////////////////////////////////////
    static MathVector<T> backSubstitution(const IMathMatrix<T>& augmented);
};

template <class T>
int GaussianElimination<T>::getMaxColumnValueRow(const IMathMatrix<T>& matrix,
    int column, int startRow)
{
  T maxSoFar = 0;
  for (int row = startRow, numRows = matrix.rows(); row < numRows; ++row)
  {
    if (matrix(row, column) > maxSoFar)
    {
      startRow = row;
      maxSoFar = matrix(row, column);
    }
  }
  return startRow;
}

template <class T>
MathVector<T> GaussianElimination<T>::operator()(const IMathMatrix<T>& coefficients,
    const MathVector<T>& constants) const
{
  if (coefficients.cols() != constants.size())
  {
    throw std::domain_error("Cannot perform GaussianElimination on matrix and vector"
        " of incorrect dimensions!");
  }

  MathMatrix<T> augmented = augmentedMatrix(coefficients, constants);
  augmented = forwardElimination(augmented, usePivot);

  MathVector<T> result = backSubstitution(augmented);

  return result;
}

template <class T>
MathMatrix<T> GaussianElimination<T>::augmentedMatrix
    (const IMathMatrix<T>& A, const MathVector<T>& b)
{
  if (A.cols() != b.size())
  {
    throw std::domain_error("Cannot perform GaussianElimination on matrix and vector"
        " of incorrect dimensions!");
  }

  MathMatrix<T> augmented(A.rows(), A.cols() + 1);

  for (int row = 0, numRows = augmented.rows(); row < numRows; ++row)
  {
    for (int col = 0, numCols = augmented.cols(); col < numCols; ++col)
    {
      if (col != numCols - 1)
      {
        augmented(row, col) = A(row, col);
      }
      else
      {
        augmented(row, col) = b[row];
      }
    }
  }
  return augmented;
}

template <class T>
MathMatrix<T> GaussianElimination<T>::forwardElimination
    (const IMathMatrix<T>& augmented, bool partialPivot)
{
  MathMatrix<T> result(augmented);
  for (int k = 0, kSize = result.rows() - 1; k < kSize; ++k)
  {
    for (int i = k + 1, iSize = result.rows(); i < iSize; ++i)
    {
      if (result(k, k) == 0)
      {
        if (partialPivot && (k != kSize - 1))
        {
          // Find max value to swap with
          int swapRow = getMaxColumnValueRow(result, k, k);
          if (swapRow != k)
          {
            result.swap(k, swapRow);
          }
          else
          {
            throw std::domain_error("Divide by zero encountered in Gaussian Forward "
                "Elimination! Unable to Pivot!");
          }
        }
        else {
          throw std::domain_error("Divide by zero encountered in Gaussian Forward "
              "Elimination!");
        }
      }
      double ratio = static_cast<double>(result(i, k)) / result(k, k);
      for (int j = k + 1, jSize = result.cols(); j < jSize; ++j)
      {
        result(i, j) -= static_cast<T>(ratio * result(k, j));
      }
    }
  }
  return result;
}

template <class T>
MathVector<T> GaussianElimination<T>::backSubstitution
    (const IMathMatrix<T>& augmented)
{
  MathVector<T> result(augmented.rows());
  T tempSolution;
  int xLoc = augmented.cols() - 1;
  for (int i = augmented.rows() - 1; i >= 0; --i)
  {
    tempSolution = augmented(i, xLoc);
    for (int j = i + 1, jSize = augmented.rows(); j < jSize; ++j)
    {
      tempSolution -= augmented(i, j) * result[j];
    }
    if (augmented(i, i) == 0)
    {
      throw std::domain_error("Divide by zero encountered in backSubstitution!");
    }
    result[i] = static_cast<T>(tempSolution / static_cast<double>(augmented(i, i)));
  }

  return result;
}

#endif
