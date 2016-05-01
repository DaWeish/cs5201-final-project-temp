////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   Array.hpp
// brief  Implementation of the Array class
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include <algorithm>

#include "Array.h"

template <class T>
Array<T>::Array() : mySize(0), myData(nullptr) {}

template <class T>
Array<T>::Array(Array<T>::size_type size) : mySize(size)
{
  myData = new T[mySize]();
}

template <class T>
Array<T>::Array(const Array<T>& other) : mySize(other.mySize)
{
  myData = new T[mySize];
  std::copy(other.myData, other.myData + other.mySize, myData);
}

template <class T>
Array<T>::Array(Array<T>&& other) : mySize(other.mySize), myData(other.myData)
{
  other.myData = nullptr;
}

template <class T>
Array<T>::~Array()
{
  delete[] myData;
}

template <class T>
typename Array<T>::value_type& Array<T>::operator[](Array<T>::size_type index)
{
  return myData[index];
}

template <class T>
const typename Array<T>::value_type& Array<T>::operator[](Array<T>::size_type index) const
{
  return myData[index];
}

template <class T>
Array<T>& Array<T>::operator=(Array<T> other) noexcept
{
  this->swap(other);
  return *this;
}

template <class T>
typename Array<T>::value_type& Array<T>::at(Array<T>::size_type index)
{
  if (index >= mySize)
  {
    throw std::out_of_range("Invalid index to Array::at()");
  }

  return myData[index];
}

template <class T>
const typename Array<T>::value_type& Array<T>::at(Array<T>::size_type index) const
{
  if (index >= mySize)
  {
    throw std::out_of_range("Invalid index to ArrayList::at()");
  }

  return myData[index];
}

template <class T>
typename Array<T>::iterator Array<T>::begin() noexcept
{
  return myData;
}

template <class T>
typename Array<T>::iterator Array<T>::end() noexcept
{
  return myData + mySize;
}

template <class T>
typename Array<T>::const_iterator Array<T>::begin() const noexcept
{
  return myData;
}

template <class T>
typename Array<T>::const_iterator Array<T>::end() const noexcept
{
  return myData + mySize;
}

template <class T>
typename Array<T>::size_type Array<T>::size() const noexcept
{
  return mySize;
} 

template <class T>
void Array<T>::swap(Array<T>& other) noexcept
{
  std::swap(myData, other.myData);
  std::swap(mySize, other.mySize);

  return;
}

template <class T>
bool operator==(const Array<T>& lhs, const Array<T>& rhs)
{
  if (lhs.size() != rhs.size())
  {
    return false;
  }

  for (auto left = lhs.begin(), right = rhs.begin(), end = lhs.end();
      left != end; ++left, ++right)
  {
    if (*left != *right)
    {
      return false;
    }
  }

  return true;
}

template <class T>
bool operator!=(const Array<T>& lhs, const Array<T>& rhs)
{
  return !(lhs == rhs);
}

template <class T>
void swap(Array<T>& lhs, Array<T>& rhs) noexcept
{
  lhs.swap(rhs);
}
