////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   MathVector.hpp
// brief  Implementation of class to represent a mathematical vector
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <cmath>

#include "MathVector.h"

template <class T>
MathVector<T> operator+(MathVector<T> lhs, const MathVector<T>& rhs)
{
  lhs += rhs;
  return lhs;
}

template <class T>
MathVector<T> operator-(MathVector<T> lhs, const MathVector<T>& rhs)
{
  lhs -= rhs;
  return lhs;
}

template <class T>
MathVector<T> operator-(MathVector<T> vector)
{
  for (auto& value : vector)
  {
    value = -value;
  }

  return vector;
}

template <class T>
MathVector<T> operator*(T scaler, MathVector<T> vector)
{
  return (vector *= scaler);
}

template <class T>
MathVector<T> operator*(MathVector<T> vector, T scaler)
{
  return (vector *= scaler);
}

template <class T>
typename MathVector<T>::value_type operator*(const MathVector<T>& lhs, const MathVector<T>& rhs)
{
  return lhs.dotProduct(rhs);
}

template <class T>
MathVector<T>::MathVector() {}

template <class T>
MathVector<T>::MathVector(size_type size) : myValues(size) {}

template <class T>
MathVector<T>::MathVector(const MathVector<T>& other) : myValues(other.myValues) {}

template <class T>
MathVector<T>::MathVector(const Array<T>& other) : myValues(other) {}

template <class T>
MathVector<T>::MathVector(MathVector<T>&& other) : myValues(std::move(other.myValues)) {}

template <class T>
MathVector<T>::MathVector(Array<T>&& other) : myValues(std::move(other)) {}

template <class T>
MathVector<T>::~MathVector() {}

template <class T>
typename MathVector<T>::iterator MathVector<T>::begin() noexcept
{
  return myValues.begin();
}

template <class T>
typename MathVector<T>::iterator MathVector<T>::end() noexcept
{
  return myValues.end();
}

template <class T>
typename MathVector<T>::const_iterator MathVector<T>::begin() const noexcept
{
  return myValues.begin();
}

template <class T>
typename MathVector<T>::const_iterator MathVector<T>::end() const noexcept
{
  return myValues.end();
}

template <class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other)
{
  if (other.myValues.size() != myValues.size())
  {
    throw std::length_error("MathVectors must have the same dimensions for +=!");
  }

  for (auto thisIter = begin(), otherIter = other.begin(), endIter = end();
      thisIter != endIter; ++thisIter, ++otherIter)
  {
    (*thisIter) += (*otherIter);
  }

  return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other)
{
  if (other.myValues.size() != myValues.size())
  {
    throw std::length_error("MathVectors must have the same dimensions for -=!");
  }

  for (auto thisIter = begin(), otherIter = other.begin(), endIter = end(); 
      thisIter != endIter; ++thisIter, ++otherIter)
  {
    (*thisIter) -= (*otherIter);
  }

  return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator*=(MathVector<T>::value_type scaler)
{
  for (value_type& value : myValues)
  {
    value *= scaler;
  }

  return *this;
}

template <class T>
bool operator==(const MathVector<T>& lhs, const MathVector<T>& rhs)
{
  return (lhs.myValues == rhs.myValues);
}

template <class T>
bool operator!=(const MathVector<T>& lhs, const MathVector<T>& rhs)
{
  return !(lhs == rhs);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const MathVector<T>& vector)
{
  for (T value : vector)
  {
  os << std::setw(10) << value << " ";
  }
  return os;
}

template <class T>
std::istream& operator>>(std::istream& is, MathVector<T>& vector)
{
  int size = vector.size();
  T value;
  for (auto i = 0; i < size; ++i)
  {
    if (is.good())
    {
      is >> value;
      vector[i] = value;
    }
    else
    {
      throw std::domain_error("Could not parse MathVector from stream");
    }
  }
  return is;
}

// Can throw std::out_of_range exception for an invalid index
template <class T>
typename MathVector<T>::value_type& MathVector<T>::operator[](MathVector<T>::size_type index)
{
  return myValues.at(index);
}

// Can throw std::out_of_range exception for an invalid index
template <class T>
const typename MathVector<T>::value_type& MathVector<T>::operator[](MathVector<T>::size_type
    index) const
{
  return myValues.at(index);
}

template <class T>
MathVector<T>& MathVector<T>::operator=(MathVector<T> other) noexcept
{
  myValues.swap(other.myValues);
  return *this;
}

template <class T>
typename MathVector<T>::value_type MathVector<T>::dotProduct(const MathVector<T>& other) const
{
  if (size() != other.size())
  {
    throw std::length_error(
        "Both MathVectors must have the same size to compute dotProduct!");
  }

  MathVector<T>::value_type result = 0;
  for (auto thisIter = begin(), otherIter = other.begin(), endIter = end();
      thisIter != endIter; ++thisIter, ++otherIter)
  {
    result += (*thisIter) * (*otherIter);
  }

  return result;
}

template <class T>
typename MathVector<T>::value_type MathVector<T>::getMagnitude() const
{
  return sqrt(this->dotProduct(*this));
}

template <class T>
typename MathVector<T>::size_type MathVector<T>::size() const noexcept
{
  return myValues.size();
}

template <class T>
void MathVector<T>::zero() noexcept
{
  for (value_type& value : myValues)
  {
    value = 0;
  }

  return;
}
