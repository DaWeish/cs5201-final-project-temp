/*
 * Connor Walsh
 * MathMatrix.hpp : Implementation file for MathMatrix class
 */

#include <stdexcept>
#include <memory>
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
  myRows = Array<MathVector<T>*>(other.getRows());
  for (int i = 0, numRows = other.getRows(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(*(other.myRows[i]));
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
  if (myRows.size() != rhs.rows())
  {
    for (auto& row : myRows)
    {
      delete row;
    }
    myRows = Array<MathVector<T>*>(rhs.rows());
  }

  myColumns = rhs.cols();
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    myRows[i] = new MathVector<T>(myColumns);
    for (int j = 0; j < (int)myColumns; ++j)
    {
      at(i, j) = rhs(i, j);
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
MathMatrix<T>& MathMatrix<T>::opPlusEquals(const IMathMatrix<T>& rhs)
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
MathMatrix<T>& MathMatrix<T>::opMinusEquals(const IMathMatrix<T>& rhs)
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
MathMatrix<T>& MathMatrix<T>::opTimesEquals(const T& scaler)
{
  for (auto& row : myRows)
  {
    (*row) *= scaler;
  }
  return *this;
}

template <class T>
std::unique_ptr<IMathMatrix<T>> MathMatrix<T>::opPlus
    (const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  std::unique_ptr<IMathMatrix<T>> result(new MathMatrix<T>(*this));
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < (int)myColumns; ++col)
    {
      (*result)(row, col) += rhs(row, col);
    }
  }

  return result;
}

template <class T>
std::unique_ptr<IMathMatrix<T>> MathMatrix<T>::opMinus
    (const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != rhs.cols())
  {
    throw std::domain_error("Cannot subtract two matrices of differing dimensions!");
  }

  std::unique_ptr<IMathMatrix<T>> result(new MathMatrix<T>(*this));
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < (int)myColumns; ++col)
    {
      (*result)(row, col) -= rhs(row, col);
    }
  }

  return result;
}

template <class T>
std::unique_ptr<IMathMatrix<T>> MathMatrix<T>::opMinus() const
{
  std::unique_ptr<IMathMatrix<T>> result(new MathMatrix<T>(*this));
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < (int)myColumns; ++col)
    {
      (*result)(row, col) = -((*result)(row, col));
    }
  }
  return result;
}

template <class T>
std::unique_ptr<IMathMatrix<T>> MathMatrix<T>::opTimes
    (const IMathMatrix<T>& rhs) const
{
  if (myColumns != rhs.rows()) {
    throw std::domain_error("Cannot multiply matrices of incorrect dimensions!");
  }

  std::unique_ptr<IMathMatrix<T>> result
    (new MathMatrix<T>(myRows.size(), rhs.cols()));
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
      (*result)(lhsRow, rhsCol) = sum;
    }
  }
  return result;
}

template <class T>
MathVector<T> MathMatrix<T>::opTimes(const MathVector<T>& rhs) const
{
  return rhs;
}

template <class T>
std::unique_ptr<IMathMatrix<T>> MathMatrix<T>::opTimes(const T& scaler) const
{
  std::unique_ptr<IMathMatrix<T>> result(new MathMatrix<T>(*this));
  (*result) *= scaler;
  return result;
}

template <class T>
std::unique_ptr<IMathMatrix<T>> MathMatrix<T>::getTranspose() const
{
  std::unique_ptr<IMathMatrix<T>> result(new MathMatrix<T>(myColumns, getRows()));
  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    for (int j = 0; j < (int)myColumns; ++j)
    {
      (*result)(i, j) = this->at(j, i);
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
void MathMatrix<T>::swapRows(size_t row1, size_t row2)
{
  std::swap(myRows[row1], myRows[row2]);
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
