/*
 * author Connor Walsh
 * file   GaussianEliminationSolver.hpp
 * brief  Implementation file for the GaussianEliminationSolver class
 */

#include <stdexcept>

#include "GaussianEliminationSolver.h"
#include "../math_matrix/IMathMatrix.h"
#include "../math_matrix/MathMatrix.h"
#include "../MathVector.h"

template <class T>
int GaussianEliminationSolver<T>::getMaxColumnValueRow(const IMathMatrix<T>& matrix,
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
MathVector<T> GaussianEliminationSolver<T>::operator()
  (const IMathMatrix<T>& coefficients,
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
MathMatrix<T> GaussianEliminationSolver<T>::augmentedMatrix
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
MathMatrix<T> GaussianEliminationSolver<T>::forwardElimination
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
            result.swapRows(k, swapRow);
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
MathVector<T> GaussianEliminationSolver<T>::backSubstitution
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

