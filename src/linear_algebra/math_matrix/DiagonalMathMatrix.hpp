/*
 * Connor Walsh
 * DiagonalMathMatrix.hpp : Implementation file for DiagonalMathMatrix class
 */

#include <stdexcept>

#include "DiagonalMathMatrix.h"
#include "MathMatrix.h"

template <class T>
DiagonalMathMatrix<T>::DiagonalMathMatrix(size_t rows, size_t cols) : myRows(rows), 
  myColumns(cols)
{
  myDiagonal = new MathVector<T>(myRows);
}

template <class T>
DiagonalMathMatrix<T>::DiagonalMathMatrix(const DiagonalMathMatrix<T>& other) 
: myRows(other.myRows), myColumns(other.myColumns)
{
  myDiagonal = new MathVector<T>(*(other.myDiagonal));
}

template <class T>
DiagonalMathMatrix<T>::DiagonalMathMatrix(DiagonalMathMatrix<T>&& other) 
: myRows(other.myRows), myColumns(other.myColumns)
{
  myDiagonal = other.myDiagonal;
  other.myDiagonal = nullptr;
  other.myColumns = 0;
  other.myRows = 0;
}

template <class T>
DiagonalMathMatrix<T>::~DiagonalMathMatrix<T>()
{
  delete myDiagonal;
}

template <class T>
DiagonalMathMatrix<T>& DiagonalMathMatrix<T>::operator=(DiagonalMathMatrix<T> rhs)
{
  swap(rhs);
  return *this;
}

template <class T>
void DiagonalMathMatrix<T>::swap(DiagonalMathMatrix<T>& other)
{
  std::swap(myColumns, other.myColumns);
  std::swap(myRows, other.myRows);
  std::swap(myDiagonal, other.myDiagonal);
  return;
}

template <class T>
DiagonalMathMatrix<T>& DiagonalMathMatrix<T>::opAssign(const IMathMatrix<T>& rhs)
{
  if (myRows != (int)rhs.rows())
  {
    delete myDiagonal;
    myDiagonal = new MathVector<T>(rhs.rows());
    myRows = rhs.rows();
  }
  myColumns = rhs.cols();

  for (int i = 0; i < myRows; ++i)
  {
    (*myDiagonal)[i] = rhs(i, i);
  }

  return *this;
}

template <class T>
bool DiagonalMathMatrix<T>::opEquality(const IMathMatrix<T>& rhs) const
{
  if (myColumns != (int)rhs.cols()) return false;
  if (myRows != (int)rhs.rows()) return false;

  for (int i = 0; i < myRows; ++i)
  {
    for (int j = 0; j < myColumns; ++j)
    {
      if (at(i, j) != rhs(i, j)) return false;
    }
  }
  return true;
}

// This will still be a diagonal matrix even after plus equals
template <class T>
DiagonalMathMatrix<T>& DiagonalMathMatrix<T>::opPlusEquals(const IMathMatrix<T>& rhs)
{
  if (myRows == (int)rhs.rows() && myColumns == (int)rhs.cols())
  {
    for (int i = 0; i < myRows; ++i)
    {
      (*myDiagonal)[i] += rhs(i, i);
    }
  }
  else
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }
  return *this;
}

template <class T>
DiagonalMathMatrix<T>& DiagonalMathMatrix<T>::opMinusEquals
    (const IMathMatrix<T>& rhs)
{
  if (myRows == (int)rhs.rows() && myColumns == (int)rhs.cols())
  {
    for (int i = 0; i < myRows; ++i)
    {
      (*myDiagonal)[i] -= rhs(i, i);
    }
  }
  else
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }
  return *this;
}

template <class T>
DiagonalMathMatrix<T>& DiagonalMathMatrix<T>::opTimesEquals(const T& scaler)
{
  for (int i = 0; i < myRows; ++i)
  {
    (*myDiagonal)[i] *= scaler;
  }
  return *this;
}

template <class T>
MathMatrix<T>* DiagonalMathMatrix<T>::opPlus(const IMathMatrix<T>& rhs) const
{
  if (myRows != (int)rhs.rows() || myColumns != (int)rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  MathMatrix<T>* result = new MathMatrix<T>(myRows, myColumns);
  for (int row = 0; row < myRows; ++row)
  {
    for (int col = 0; col < myColumns; ++col)
    {
      if (row == col)
      {
        result->at(row, col) = (*myDiagonal)[row] + rhs(row, col);
      }
      else
      {
        result->at(row, col) = rhs(row, col);
      }
    }
  }
  return result;
}

template <class T>
MathMatrix<T>* DiagonalMathMatrix<T>::opMinus
    (const IMathMatrix<T>& rhs) const
{
  if (myRows != (int)rhs.rows() || myColumns != (int)rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  MathMatrix<T>* result = new MathMatrix<T>(myRows, myColumns);
  for (int row = 0; row < myRows; ++row)
  {
    for (int col = 0; col < myColumns; ++col)
    {
      if (row == col)
      {
        result->at(row, col) = (*myDiagonal)[row] - rhs(row, col);
      }
      else
      {
        result->at(row, col) = -rhs(row, col);
      }
    }
  }
  return result;
}

template <class T>
DiagonalMathMatrix<T>* DiagonalMathMatrix<T>::opMinus() const
{
  DiagonalMathMatrix<T>* result = new DiagonalMathMatrix<T>(*this);
  for (int i = 0; i < myRows; ++i)
  {
    (*(result->myDiagonal))[i] = -(*(result->myDiagonal))[i];
  }

  return result;
}

template <class T>
MathMatrix<T>* DiagonalMathMatrix<T>::opTimes(const IMathMatrix<T>& rhs) const
{
  if (myColumns != (int)rhs.rows()) {
    throw std::domain_error("Cannot multiply matrices of incorrect dimensions!");
  }

  MathMatrix<T>* result = new MathMatrix<T>(myRows, rhs.cols());
  for (int lhsRow = 0; lhsRow < myRows; ++lhsRow)
  {
    for (int rhsCol = 0, numCols = rhs.cols(); rhsCol < numCols; ++rhsCol)
    {
      result->at(lhsRow, rhsCol) = rhs(lhsRow, rhsCol) * (*myDiagonal)[lhsRow];
    }
  }
  return result;
}

template <class T>
DiagonalMathMatrix<T>* DiagonalMathMatrix<T>::opTimes(const T& scaler) const
{
  DiagonalMathMatrix<T>* result = new DiagonalMathMatrix<T>(*this);
  return &(result->opTimesEquals(scaler));
}

template <class T>
MathVector<T>& DiagonalMathMatrix<T>::at(size_t index)
{
  std::cout << index;
  throw std::domain_error("Cannot retrieve a math vector from DiagonalMatrix");
}

template <class T>
const MathVector<T>& DiagonalMathMatrix<T>::at(size_t index) const
{
  std::cout << index;
  throw std::domain_error("Cannot retrieve a math vector from DiagonalMatrix");
}

template <class T>
T& DiagonalMathMatrix<T>::at(size_t row, size_t column)
{
  if (row >= 0 && (int)row < myRows && column >= 0 && (int)column < myColumns)
  {
    if (row == column) return (*myDiagonal)[row];
    else 
    {
      throw std::domain_error("Cannot assign to non diagonal values!");
    }
  }
  else
  {
    throw std::domain_error("Index was out of bounds");
  }
}

template <class T>
const T& DiagonalMathMatrix<T>::at(size_t row, size_t column) const
{
  if (row >= 0 && (int)row < myRows && column >= 0 && (int)column < myColumns)
  {
    if (row == column) return (*myDiagonal)[row];
    else return zero; 
  }
  else
  {
    throw std::domain_error("Index was out of bounds");
  }
}

template <class T>
size_t DiagonalMathMatrix<T>::getRows() const
{
  return myRows;
}

template <class T>
size_t DiagonalMathMatrix<T>::getCols() const
{
  return myColumns;
}

template <class T>
void DiagonalMathMatrix<T>::swapRows(size_t row1, size_t row2)
{
  (*myDiagonal)[row1] = 0;
  (*myDiagonal)[row2] = 0;
}

template <class T>
void DiagonalMathMatrix<T>::printToStream(std::ostream& os) const
{
  T value;
  for (int i = 0; i < myRows; ++i)
  {
    for (int j = 0; j < myColumns; ++j)
    {
      (i == j) ? value = (*myDiagonal)[i] : value = 0;
      os << std::setw(10) << value << " ";
    }
    os << "\n";
  }
}

template <class T>
void DiagonalMathMatrix<T>::readFromStream(std::istream& is)
{
  int temp;
  is >> temp;
  throw std::domain_error("Cannot read DiagonalMathMatrix from stream!");
}
