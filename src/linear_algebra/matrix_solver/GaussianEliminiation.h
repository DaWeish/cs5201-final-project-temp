////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   Gaussian.h
// brief  Class to represent a gaussian elimination functor
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "MathMatrix2D.h"
#include "MathVector.h"

////////////////////////////////////////////////////////////////////////////////
// class GaussianElimination
// brief This class implements a functor for performing Gaussian Elimination
////////////////////////////////////////////////////////////////////////////////
template <class T>
class GaussianElimination
{
  protected:
    ////////////////////////////////////////////////////////////////////////////
    // fn getMaxColumnValueRow
    // brief This function is used during pivoting to get the row index which
    //    is to be pivoted with the current row
    ////////////////////////////////////////////////////////////////////////////
    static int getMaxColumnValueRow(const MathMatrix2D<T>& matrix, int column,
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
    MathVector<T> operator()(const MathMatrix2D<T>& coefficients, 
        MathVector<T> constants, bool partialPivot = false) const;

    ////////////////////////////////////////////////////////////////////////////
    // fn augmentedMatrix
    // brief This function creates an augmented matrix from a set of coefficients
    //    and a constants MathVector
    // pre  constants' size must be equal to coefficients.rows()
    // post returns a matrix of size coefficients.rows() x 
    //    coefficients.columns() + 1 that is an augmented matrix of the inputs
    ////////////////////////////////////////////////////////////////////////////
    static MathMatrix2D<T> augmentedMatrix(const MathMatrix2D<T>& coefficients,
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
    static MathMatrix2D<T> forwardElimination(MathMatrix2D<T> augmented,
        bool partialPivot = false);

    ////////////////////////////////////////////////////////////////////////////
    // fn backSubstitution
    // brief Retrives the values represented by the forward elminiation matrix
    // pre augmented is in echelon form
    // post returns a new matrix where the rightmost column values are replaced
    //    with the solutions to the equation Ax=b represented by augmented
    ////////////////////////////////////////////////////////////////////////////
    static MathMatrix2D<T> backSubstitution(MathMatrix2D<T> augmented);
};

template <class T>
int GaussianElimination<T>::getMaxColumnValueRow(const MathMatrix2D<T>& matrix,
    int column, int startRow)
{
  T maxSoFar = 0;
  for (int row = startRow, numRows = matrix.rows(); row < numRows; ++row)
  {
    if (matrix[row][column] > maxSoFar)
    {
      startRow = row;
      maxSoFar = matrix[row][column];
    }
  }
  return startRow;
}

template <class T>
MathVector<T> GaussianElimination<T>::operator()(const MathMatrix2D<T>& coefficients,
    MathVector<T> constants, bool partialPivot) const
{
  if (coefficients.columns() != constants.size())
  {
    throw std::domain_error("Cannot perform GaussianElimination on matrix and vector"
        " of incorrect dimensions!");
  }

  MathMatrix2D<T> augmented = augmentedMatrix(coefficients, constants);
  augmented = forwardElimination(augmented, partialPivot);
  augmented = backSubstitution(augmented);

  int xLoc = augmented.columns() - 1;
  for (int row = 0, numRows = constants.size(); row < numRows; ++row)
  {
    constants[row] = augmented[row][xLoc];
  }
  return constants;
}

template <class T>
MathMatrix2D<T> GaussianElimination<T>::augmentedMatrix
    (const MathMatrix2D<T>& coefficients, const MathVector<T>& constants)
{
  if (coefficients.columns() != constants.size())
  {
    throw std::domain_error("Cannot perform GaussianElimination on matrix and vector"
        " of incorrect dimensions!");
  }

  MathMatrix2D<T> augmented(coefficients.rows(), coefficients.columns() + 1);

  for (int row = 0, numRows = augmented.rows(); row < numRows; ++row)
  {
    for (int col = 0, numCols = augmented.columns(); col < numCols; ++col)
    {
      if (col != numCols - 1)
      {
        augmented[row][col] = coefficients[row][col];
      }
      else
      {
        augmented[row][col] = constants[row];
      }
    }
  }

  return augmented;
}

template <class T>
MathMatrix2D<T> GaussianElimination<T>::forwardElimination(MathMatrix2D<T> augmented,
    bool partialPivot)
{
  for (int k = 0, kSize = augmented.rows() - 1; k < kSize; ++k)
  {
    for (int i = k + 1, iSize = augmented.rows(); i < iSize; ++i)
    {
      if (augmented[k][k] == 0)
      {
        if (partialPivot && (k != kSize - 1))
        {
          // Find max value to swap with
          int swapRow = getMaxColumnValueRow(augmented, k, k);
          if (swapRow != k)
          {
            augmented.swap(k, swapRow);
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
      double ratio = static_cast<double>(augmented[i][k]) / augmented[k][k];
      for (int j = k + 1, jSize = augmented.columns(); j < jSize; ++j)
      {
        augmented[i][j] -= static_cast<T>(ratio * augmented[k][j]);
      }
    }
  }
  return augmented;
}

template <class T>
MathMatrix2D<T> GaussianElimination<T>::backSubstitution(MathMatrix2D<T> augmented)
{
  int xLoc = augmented.columns() - 1;
  for (int i = augmented.rows() - 1; i >= 0; --i)
  {
    for (int j = i + 1, jSize = augmented.rows(); j < jSize; ++j)
    {
      augmented[i][xLoc] -= augmented[i][j] * augmented[j][xLoc];
    }
    augmented[i][xLoc] = static_cast<T>(augmented[i][xLoc] 
        / static_cast<double>(augmented[i][i]));
  }

  return augmented;
}
