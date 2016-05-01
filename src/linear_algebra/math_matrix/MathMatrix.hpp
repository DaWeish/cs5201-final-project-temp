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
  myRows = Array<MathVector<T>*>(other.getRows());
  for (auto i = 0, numRows = (int)other.getRows(); i < numRows; ++i)
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
    for (int j = 0; j < myColumns; ++j)
    {
      at(i, j) = rhs(i, j);
    }
  }

  return *this;
}

template <class T>
bool MathMatrix<T>::opEquality(const IMathMatrix<T>& rhs) const
{
  if (myColumns != (int)rhs.cols()) return false;
  if (myRows.size() != rhs.rows()) return false;

  for (int i = 0, numRows = myRows.size(); i < numRows; ++i)
  {
    for (int j = 0; j < myColumns; ++j)
    {
      if (at(i, j) != rhs(i, j)) return false;
    }
  }
  return true;
}

template <class T>
MathMatrix<T>& MathMatrix<T>::opPlusEquals(const IMathMatrix<T>& rhs)
{
  if (myRows.size() == rhs.rows() && myColumns == (int)rhs.cols())
  {
    for (auto i = 0, numRows = (int)getRows(); i < numRows; ++i)
    {
      for (auto j = 0; j < myColumns; ++j)
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
  if (myRows.size() == rhs.rows() && myColumns == (int)rhs.cols())
  {
    for (auto i = 0, numRows = (int)getRows(); i < numRows; ++i)
    {
      for (auto j = 0; j < myColumns; ++j)
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
MathMatrix<T>* MathMatrix<T>::opPlus(const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != (int)rhs.cols())
  {
    throw std::domain_error("Cannot add two matrices of differing dimensions!");
  }

  MathMatrix<T>* result = new MathMatrix<T>(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < myColumns; ++col)
    {
      result->at(row, col) += rhs(row, col);
    }
  }

  return result;
}

template <class T>
MathMatrix<T>* MathMatrix<T>::opMinus(const IMathMatrix<T>& rhs) const
{
  if (myRows.size() != rhs.rows() || myColumns != (int)rhs.cols())
  {
    throw std::domain_error("Cannot subtract two matrices of differing dimensions!");
  }

  MathMatrix<T>* result = new MathMatrix<T>(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < myColumns; ++col)
    {
      result->at(row, col) -= rhs(row, col);
    }
  }

  return result;
}

template <class T>
MathMatrix<T>* MathMatrix<T>::opMinus() const
{
  MathMatrix<T>* result = new MathMatrix<T>(*this);
  for (int row = 0, numRows = myRows.size(); row < numRows; ++row)
  {
    for (int col = 0; col < myColumns; ++col)
    {
      result->at(row, col) = -result->at(row, col);
    }
  }
  return result;
}

template <class T>
MathMatrix<T>* MathMatrix<T>::opTimes(const IMathMatrix<T>& rhs) const
{
  if (myColumns != (int)rhs.rows()) {
    throw std::domain_error("Cannot multiply matrices of incorrect dimensions!");
  }

  MathMatrix<T>* result = new MathMatrix<T>(myRows.size(), rhs.cols());
  T sum;
  for (int lhsRow = 0, numRows = myRows.size(); lhsRow < numRows; ++lhsRow)
  {
    for (int rhsCol = 0, numCols = rhs.cols(); rhsCol < numCols; ++rhsCol)
    {
      sum = 0;
      for (int element = 0; element < myColumns; ++element)
      {
        sum += at(lhsRow, element) * rhs(element, rhsCol);
      }
      result->at(lhsRow, rhsCol) = sum;
    }
  }
  return result;
}

template <class T>
MathMatrix<T>* MathMatrix<T>::opTimes(const T& scaler) const
{
  MathMatrix<T>* result = new MathMatrix<T>(*this);
  return &(result->opTimesEquals(scaler));
}

template <class T>
MathVector<T>& MathMatrix<T>::at(size_t index)
{
  return *(myRows.at(index));
}

template <class T>
const MathVector<T>& MathMatrix<T>::at(size_t index) const
{
  return *(myRows.at(index));
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
  for (auto i = 0, numRows = (int)getRows(); i < numRows; ++i)
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
