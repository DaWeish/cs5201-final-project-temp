/*
 * Connor Walsh
 * MathMatrix.hpp : Implementation file for MathMatrix class
 */

#include <stdexcept>
#include <sstream>

#include "MathMatrix.h"

template <class T>
MathMatrix<T>::MathMatrix(size_t rows, size_t cols) : myColumns(cols)
{
  myRows = Array<MathVector<T>*>(rows);
  for (auto& row : myRows)
  {
    row = new MathVector<T>(myColumns);
  }
}

template <class T>
MathMatrix<T>::MathMatrix(const MathMatrix<T>& other) : myColumns(other.myColumns)
{
  myRows = Array<MathVector<T>*>(other.myRows.size());
  for (int i = 0, numRows = other.getRows(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(*(other.myRows[i]));
  }
}

template <class T>
MathMatrix<T>::MathMatrix(const IMathMatrix<T>& other) : myColumns(other.cols())
{
  myRows = Array<MathVector<T>*>(other.rows());
  for (int i = 0, numRows = other.rows(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(myColumns);
    for (int j = 0; j < (int)myColumns; ++j)
    {
      myRows[i][j] = other(i, j);
    }
  }
}

template <class T>
MathMatrix<T>::MathMatrix(MathMatrix<T>&& other) : myColumns(other.myColumns)
{
  myRows = other.myRows;
  for (auto& row : other.myRows)
  {
    row = nullptr;
  }
  other.myColumns = 0;
}

template <class T>
MathMatrix<T>::~MathMatrix<T>()
{
  for (auto& rowPointer : myRows)
  {
    delete(rowPointer);
  }
}

template <class T>
MathMatrix<T>& MathMatrix<T>::operator=(MathMatrix<T> rhs)
{
  swap(rhs);
  return *this;
}

template <class T>
void MathMatrix<T>::swap(MathMatrix<T>& other)
{
  std::swap(myColumns, other.myColumns);
  myRows.swap(other.myRows);
  return;
}

template <class T>
MathMatrix<T>& MathMatrix<T>::opAssign(const IMathMatrix<T>& rhs)
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    myColumns = rhs.cols();
    for (auto& row : myRows)
    {
      delete row;
    }
    myRows = Array<MathVector<T>*>(rhs.rows());
    for (auto& row : myRows)
    {
      row = new MathVector<T>(myColumns);
    }
  }

  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    for (int j = 0; j < (int)myColumns; ++j)
    {
      (*(myRows.at(i)))[j] = rhs(i, j);
    }
  }

  return *this;
}

template <class T>
bool MathMatrix<T>::opEquality(const IMathMatrix<T>& rhs) const
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
bool MathMatrix<T>::operator==(const MathMatrix<T>& rhs) const
{
  if (this == &rhs) return true;
  if (myColumns != rhs.myColumns) return false;
  if (myRows.size() != rhs.myRows.size()) return false;

  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    if (*(myRows.at(i)) != *(rhs.myRows.at(i))) return false;
  }

  return true;
}

template <class T>
bool MathMatrix<T>::operator!=(const MathMatrix<T>& rhs) const
{
  return !(*this == rhs);
}

template <class T>
MathMatrix<T>& MathMatrix<T>::operator+=(const IMathMatrix<T>& rhs)
{
  if (myRows.size() == rhs.rows() && myColumns == rhs.cols())
  {
    for (int i = 0, numRows = getRows(); i < numRows; ++i)
    {
      for (int j = 0; j < (int)myColumns; ++j)
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
MathMatrix<T>& MathMatrix<T>::operator-=(const IMathMatrix<T>& rhs)
{
  if (myRows.size() == rhs.rows() && myColumns == rhs.cols())
  {
    for (int i = 0, numRows = getRows(); i < numRows; ++i)
    {
      for (int j = 0; j < (int)myColumns; ++j)
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
MathMatrix<T>& MathMatrix<T>::operator*=(const T& scaler)
{
  for (auto& row : myRows)
  {
    (*row) *= scaler;
  }
  return *this;
}

template <class T>
MathMatrix<T> MathMatrix<T>::operator+(const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  MathMatrix<T> result(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < (int)myColumns; ++col)
    {
      result.at(row, col) += rhs(row, col);
    }
  }

  return result;
}

template <class T>
MathMatrix<T> MathMatrix<T>::operator-(const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot subtract two matrices of differing dimensions!");
  }

  MathMatrix<T> result(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < (int)myColumns; ++col)
    {
      result.at(row, col) -= rhs(row, col);
    }
  }

  return result;
}

template <class T>
MathMatrix<T> MathMatrix<T>::operator-() const
{
  MathMatrix<T> result(*this);
  for (auto& row : result.myRows)
  {
    (*row) = -(*row);
  }

  return result;
}

template <class T>
MathMatrix<T> MathMatrix<T>::operator*(const IMathMatrix<T>& rhs) const
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
      for (int element = 0; element < (int)myColumns; ++element)
      {
        sum += at(lhsRow, element) * rhs(element, rhsCol);
      }
      result.at(lhsRow, rhsCol) = sum;
    }
  }
  return result;
}

template <class T>
MathMatrix<T> MathMatrix<T>::operator*(const T& scaler) const
{
  MathMatrix<T> result(*this);
  return (result *= scaler);
}

template <class T>
MathVector<T> MathMatrix<T>::operator*(const MathVector<T>& rhs) const
{
  if (myColumns != rhs.size()) {
    throw std::domain_error("Cannot multiply by MathVector of incorrect dimensions!");
  }

  T sum;
  MathVector<T> result(myRows.size());
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    sum = 0;
    for (int j = 0; j < (int)myColumns; ++j)
    {
      sum += at(i, j) * rhs[j];
    }
    result[i] = sum;
  }
  
  return result;
}

template <class T>
MathMatrix<T> MathMatrix<T>::transpose() const
{
  MathMatrix<T> result(myColumns, myRows.size());
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    for (int j = 0; j < (int)myColumns; ++j)
    {
      result(j, i) = at(i, j);
    }
  }
  return result;
}

template <class T>
T& MathMatrix<T>::at(size_t row, size_t column)
{
  return (*(myRows.at(row)))[column];
}

template <class T>
const T& MathMatrix<T>::at(size_t row, size_t column) const
{
  return (*(myRows.at(row)))[column];
}

template <class T>
size_t MathMatrix<T>::getRows() const
{
  return myRows.size();
}

template <class T>
size_t MathMatrix<T>::getCols() const
{
  return myColumns;
}

template <class T>
MathMatrix<T> MathMatrix<T>::swapRows(size_t row1, size_t row2)
{
  MathMatrix<T> result(*this);
  std::swap(result.myRows[row1], result.myRows[row2]);
  return result;
}

template <class T>
void MathMatrix<T>::printToStream(std::ostream& os) const
{
  for (int i = 0, numRows = getRows(); i < numRows; ++i)
  {
    os << *(myRows[i]) << "\n";
  }
}

template <class T>
void MathMatrix<T>::readFromStream(std::istream& is) 
{
  std::string line;
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    if (is.good())
    {
      getline(is, line);
      std::istringstream lineStream(line);

      lineStream >> *(myRows[row]);
    }
    else
    {
      break;
    }
  }
}
