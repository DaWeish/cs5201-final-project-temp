/*
 * Connor Walsh
 * UpTriangleMathMatrix.hpp : Implementation file for UpTriangleMathMatrix class
 */

#include <stdexcept>

#include "MathMatrix.h"
#include "UpTriangleMathMatrix.h"
#include "LowTriangleMathMatrix.h"

template <class T>
UpTriangleMathMatrix<T>::UpTriangleMathMatrix(size_t rows, size_t cols) 
    : myColumns(cols)
{
  myRows = Array<MathVector<T>*>(rows);
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(myColumns - i);
  }
}

template <class T>
UpTriangleMathMatrix<T>::UpTriangleMathMatrix(const UpTriangleMathMatrix<T>& other) 
    : myColumns(other.myColumns)
{
  myRows = Array<MathVector<T>*>(other.myRows.size());
  for (int i = 0, numRows = other.getRows(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(*(other.myRows[i]));
  }
}

template <class T>
UpTriangleMathMatrix<T>::UpTriangleMathMatrix(const IMathMatrix<T>& other)
  : myColumns(other.cols())
{
  myRows = Array<MathVector<T>*>(other.rows());
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(myColumns - i);
    for (int j = i; j < (int)myColumns; ++j)
    {
      at(i, j) = other(i, j);
    }
  }
}

template <class T>
UpTriangleMathMatrix<T>::UpTriangleMathMatrix(UpTriangleMathMatrix<T>&& other) 
    : myColumns(other.myColumns)
{
  myRows = other.myRows;
  for (auto& row : other.myRows)
  {
    row = nullptr;
  }
  other.myColumns = 0;
}

template <class T>
UpTriangleMathMatrix<T>::~UpTriangleMathMatrix<T>()
{
  for (auto& rowPointer : myRows)
  {
    delete(rowPointer);
  }
}

template <class T>
UpTriangleMathMatrix<T>& UpTriangleMathMatrix<T>::operator=
    (UpTriangleMathMatrix<T> rhs)
{
  swap(rhs);
  return *this;
}

template <class T>
void UpTriangleMathMatrix<T>::swap(UpTriangleMathMatrix<T>& other)
{
  std::swap(myColumns, other.myColumns);
  myRows.swap(other.myRows);
  return;
}

template <class T>
bool UpTriangleMathMatrix<T>::opEquality(const IMathMatrix<T>& rhs) const
{
  if (myColumns != rhs.cols()) return false;
  if (myRows.size() != rhs.rows()) return false;

  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    for (int j = 0; j < (int)myColumns; ++j)
    {
      if (at(i, j) != rhs(i, j)) return false;
    }
  }
  return true;
}

template <class T>
bool UpTriangleMathMatrix<T>::operator==(const UpTriangleMathMatrix<T>& rhs) const
{
  if (myColumns != rhs.myColumns) return false;
  if (myRows.size() != rhs.myRows.size()) return false;

  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    if (*(myRows[i]) != *(rhs.myRows[i])) return false;
  }

  return true;
}

template <class T>
bool UpTriangleMathMatrix<T>::operator!=(const UpTriangleMathMatrix<T>& rhs) const
{
  return !(*this == rhs);
}

template <class T>
UpTriangleMathMatrix<T>& UpTriangleMathMatrix<T>::opPlusEquals
    (const IMathMatrix<T>& rhs)
{
  if (myRows.size() == rhs.rows() && myColumns == rhs.cols())
  {
    for (int i = 0, numRows = getRows(); i < numRows; ++i)
    {
      for (int j = i; j < (int)myColumns; ++j)
      {
        at(i, j) += rhs(i, j);
      }
    }
    return *this;
  }
  else
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }
}

template <class T>
UpTriangleMathMatrix<T>& UpTriangleMathMatrix<T>::opMinusEquals
    (const IMathMatrix<T>& rhs)
{
  if (myRows.size() == rhs.rows() && myColumns == rhs.cols())
  {
    for (int i = 0, numRows = getRows(); i < numRows; ++i)
    {
      for (int j = i; j < (int)myColumns; ++j)
      {
        at(i, j) -= rhs(i, j);
      }
    }
    return *this;
  }
  else
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }
}

template <class T>
UpTriangleMathMatrix<T>& UpTriangleMathMatrix<T>::opTimesEquals
    (const IMathMatrix<T>& rhs)
{
  MathMatrix<T> result = (*this) * rhs;
  (*this) = result;
  return *this;
}

template <class T>
UpTriangleMathMatrix<T>& UpTriangleMathMatrix<T>::opTimesEquals(const T& scaler)
{
  for (auto& row : myRows)
  {
    (*row) *= scaler;
  }
  return *this;
}

template <class T>
MathMatrix<T> UpTriangleMathMatrix<T>::operator+
    (const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  MathMatrix<T> result(rhs);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = row; col < myColumns; ++col)
    {
      result(row, col) += at(row, col);
    }
  }
  return result;
}

template <class T>
UpTriangleMathMatrix<T> UpTriangleMathMatrix<T>::operator+
    (const UpTriangleMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  UpTriangleMathMatrix<T> result(rhs);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    *(result.myRows[row]) += *(myRows[row]);
  }
  return result;
}

template <class T>
MathMatrix<T> UpTriangleMathMatrix<T>::operator-(const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  MathMatrix<T> result(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = row; col < myColumns; ++col)
    {
      result(row, col) -= rhs(row, col);
    }
  }
  return result;
}

template <class T>
UpTriangleMathMatrix<T> UpTriangleMathMatrix<T>::operator-
    (const UpTriangleMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  UpTriangleMathMatrix<T> result(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    *(result.myRows[row]) -= *(rhs.myRows[row]);
  }
  return result;
}

template <class T>
UpTriangleMathMatrix<T> UpTriangleMathMatrix<T>::operator-() const
{
  UpTriangleMathMatrix<T> result(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
      *result.myRows[row] = -(*(result.myRows[row]));
  }
  return result;
}

template <class T>
MathMatrix<T> UpTriangleMathMatrix<T>::operator*(const IMathMatrix<T>& rhs) const
{
  if (myColumns != rhs.rows()) {
    throw std::domain_error("Cannot multiply matrices of incorrect dimensions!");
  }

  MathMatrix<T> result(myRows.size(), rhs.cols());
  T sum;
  for (int lhsRow = 0, numRows = myRows.size(); lhsRow < numRows; ++lhsRow)
  {
    for (int rhsCol = 0, numCols = rhs.cols(); rhsCol < numCols; ++rhsCol)
    {
      sum = 0;
      for (int element = lhsRow; element < (int)myColumns; ++element)
      {
        sum += at(lhsRow, element) * rhs(element, rhsCol);
      }
      result(lhsRow, rhsCol) = sum;
    }
  }
  return result;
}

template <class T>
UpTriangleMathMatrix<T> UpTriangleMathMatrix<T>::operator*
    (const UpTriangleMathMatrix<T>& rhs) const
{
  if (myColumns != rhs.rows()) {
    throw std::domain_error("Cannot multiply matrices of incorrect dimensions!");
  }

  UpTriangleMathMatrix<T> result(myRows.size(), rhs.cols());
  T sum;
  for (int lhsRow = 0, numRows = myRows.size(); lhsRow < numRows; ++lhsRow)
  {
    for (int rhsCol = 0, numCols = rhs.cols(); rhsCol < numCols; ++rhsCol)
    {
      sum = 0;
      for (int element = lhsRow; element < myColumns; ++element)
      {
        sum += at(lhsRow, element) * rhs(element, rhsCol);
      }
      result->at(lhsRow, rhsCol) = sum;
    }
  }
  return result;
}

template <class T>
UpTriangleMathMatrix<T> UpTriangleMathMatrix<T>::operator*(const T& scaler) const
{
  UpTriangleMathMatrix<T> result(*this);
  result *= scaler;
  return result;
}

template <class T>
MathVector<T> UpTriangleMathMatrix<T>::operator*(const MathVector<T>& rhs) const
{
  if (myColumns != rhs.size()) {
    throw std::domain_error("Cannot multiply by MathVector of incorrect dimensions!");
  }

  T sum;
  MathVector<T> result(myRows.size());
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    sum = 0;
    for (int j = i; j < (int)myColumns; ++j)
    {
      sum += at(i, j) * rhs[j];
    }
    result[i] = sum;
  }
  
  return result;
}

template <class T>
LowTriangleMathMatrix<T> UpTriangleMathMatrix<T>::transpose() const
{
  LowTriangleMathMatrix<T> result(myColumns, myRows.size());

  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    for (int j = i; j < (int)myColumns; ++j)
    {
      result(j, i) = at(i, j);
    }
  }
  return result;
}

template <class T>
T& UpTriangleMathMatrix<T>::at(size_t row, size_t column)
{
  if (row > column) throw std::out_of_range("Cannot assign to lower values in "
      " Upper Triangular matrix");
  return (*(myRows.at(row)))[column - row];
}

template <class T>
const T& UpTriangleMathMatrix<T>::at(size_t row, size_t column) const
{
  if (row > column) return zero;
  return (*(myRows.at(row)))[column - row];
}

template <class T>
size_t UpTriangleMathMatrix<T>::getRows() const
{
  return myRows.size();
}

template <class T>
size_t UpTriangleMathMatrix<T>::getCols() const
{
  return myColumns;
}

template <class T>
void UpTriangleMathMatrix<T>::printToStream(std::ostream& os) const
{
  T value = 0;
  for (int i = 0, numRows = getRows(); i < numRows; ++i)
  {
    for (int j = 0; j < i; ++j)
      os << std::setw(10) << value << " ";
    os << *(myRows[i]) << "\n";
  }
}

template <class T>
void UpTriangleMathMatrix<T>::readFromStream(std::istream& is)
{
  int temp;
  is >> temp;
  throw std::domain_error("Cannot read UpTriangleMathMatrix from stream!");
}
