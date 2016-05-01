////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   ArrayList.hpp
// brief  Implementation of the List ADT, parameterized for easy use.
////////////////////////////////////////////////////////////////////////////////

#include <utility>
#include <stdexcept>
#include <exception>

#include "ArrayList.h"

template <class T>
typename ArrayList<T>::pointer 
  ArrayList<T>::allocateSize(ArrayList<T>::size_type size)
{
  return static_cast<ArrayList<T>::pointer>
  ( ::operator new(sizeof(ArrayList<T>::value_type) * size));
}

template <class T>
void ArrayList<T>::copyRange(ArrayList<T>::pointer begin, ArrayList<T>::pointer end,
    ArrayList<T>::pointer target)
{
  while (begin != end)
  {
    new (target) T(*begin);
    ++begin;
    ++target;
  }
}

template <class T>
void ArrayList<T>::deleteRange(ArrayList<T>::pointer begin,
    ArrayList<T>::pointer end)
{
  while (begin != end)
  {
    begin->~T();
    ++begin;
  }
}

template <class T>
void ArrayList<T>::constructRange(ArrayList<T>::pointer begin, 
    ArrayList<T>::pointer end)
{
  while (begin != end)
  {
    new (begin) T();
    ++begin;
  }
}

template <class T>
void ArrayList<T>::constructRange(ArrayList<T>::pointer begin,
    ArrayList<T>::pointer end, const ArrayList<T>::value_type& value)
{
  while (begin != end)
  {
    new (begin) T(value);
    ++begin;
  }
}

template <class T>
void ArrayList<T>::reallocateCapacity(ArrayList<T>::size_type capacity)
{
  T* nextData = allocateSize(capacity);
  copyRange(myData, myData + mySize, nextData);

  std::swap(myData, nextData);
  std::swap(myCapacity, capacity);

  deleteRange(nextData, nextData + mySize);
  delete(nextData);

  return;
}

template <class T>
ArrayList<T>::ArrayList() : mySize(0), myCapacity(0), myData(nullptr) {}

template <class T>
ArrayList<T>::ArrayList(ArrayList<T>::size_type size) : mySize(size)
{
  if (mySize > INITIAL_MIN_CAPACITY)
  {
    myData = allocateSize(mySize);
    myCapacity = mySize;
  }
  else
  {
    myData = allocateSize(INITIAL_MIN_CAPACITY);
    myCapacity = INITIAL_MIN_CAPACITY;
  }

  constructRange(myData, myData + size);
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other)
{
  myData = allocateSize(other.mySize);
  myCapacity = other.mySize;
  copyRange(other.myData, other.myData + other.mySize, myData);
  mySize = other.mySize;
}

template <class T>
ArrayList<T>::ArrayList(ArrayList<T>&& other) : mySize(other.mySize), 
  myCapacity(other.myCapacity), myData(other.myData)
{
  other.myData = nullptr;
  other.mySize = other.myCapacity = 0;
}

template <class T>
ArrayList<T>::~ArrayList()
{
  deleteRange(myData, myData + mySize);
  delete(myData);
}

template <class T>
typename ArrayList<T>::value_type& 
  ArrayList<T>::operator[](ArrayList<T>::size_type index)
{
  return myData[index];
}

template <class T>
const typename ArrayList<T>::value_type&
  ArrayList<T>::operator[](ArrayList<T>::size_type index) const
{
  return myData[index];
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> other) noexcept
{
  this->swap(other);
  return *this;
}

template <class T>
typename ArrayList<T>::value_type& ArrayList<T>::at(ArrayList<T>::size_type index)
{
  if (index < 0 || index >= mySize)
  {
    throw std::out_of_range("Invalid index to ArrayList::at()");
  }

  return *(myData + index);
}

template <class T>
const typename ArrayList<T>::value_type& ArrayList<T>::at(ArrayList<T>::size_type
    index) const
{
  if (index < 0 || index >= mySize)
  {
    throw std::out_of_range("Invalid index to ArrayList::at()");
  }

  return *(myData + index);
}

template <class T>
typename ArrayList<T>::iterator ArrayList<T>::begin() noexcept
{
  return myData;
}

template <class T>
typename ArrayList<T>::iterator ArrayList<T>::end() noexcept
{
  return myData + mySize;
}

template <class T>
typename ArrayList<T>::const_iterator ArrayList<T>::begin() const noexcept
{
  return myData;
}

template <class T>
typename ArrayList<T>::const_iterator ArrayList<T>::end() const noexcept
{
  return myData + mySize;
}

template <class T>
typename ArrayList<T>::size_type ArrayList<T>::size() const noexcept
{
  return mySize;
} 
template <class T>
typename ArrayList<T>::size_type ArrayList<T>::capacity() const noexcept
{
  return myCapacity;
}

template <class T>
bool ArrayList<T>::empty() const noexcept
{
  return mySize == 0;
}

template <class T>
void ArrayList<T>::resize(ArrayList<T>::size_type size)
{
  if (size <= mySize)
  {
    deleteRange(myData + size, myData + mySize);
    mySize = size;
    return;
  } 
  if (size <= myCapacity)
  {
    constructRange(myData + mySize, myData + size);
    mySize = size;
    return;
  }

  // need to reallocate more space
  ArrayList<T>::size_type nextCapacity = size;
  if (nextCapacity < mySize * GROWTH_FACTOR)
  {
    nextCapacity = mySize * GROWTH_FACTOR;
  }
  reallocateCapacity(nextCapacity);
  constructRange(myData + mySize, myData + size);
  mySize = size;

  return;
}

template <class T>
void ArrayList<T>::resize(ArrayList<T>::size_type size,
    const ArrayList<T>::value_type& value)
{
  if (size <= mySize)
  {
    deleteRange(myData + size, myData + mySize);
    mySize = size;
    return;
  } 
  if (size <= myCapacity)
  {
    constructRange(myData + mySize, myData + size, value);
    mySize = size;
    return;
  }

  // need to reallocate more space
  ArrayList<T>::size_type nextCapacity = size;
  if (nextCapacity < mySize * GROWTH_FACTOR)
  {
    nextCapacity = mySize * GROWTH_FACTOR;
  }
  reallocateCapacity(nextCapacity);
  constructRange(myData + mySize, myData + size, value);
  mySize = size;

  return;
}

template <class T>
void ArrayList<T>::push_back(const ArrayList<T>::value_type& value)
{
  if (mySize != myCapacity)
  {
    new (myData + mySize) T(value);
    ++mySize;
    return;
  }

  size_type nextCapacity = 
    (myCapacity != 0) ? myCapacity * GROWTH_FACTOR : INITIAL_MIN_CAPACITY;
  reallocateCapacity(nextCapacity);

  new (myData + mySize) T(value);
  ++mySize;

  return;
}

template <class T>
void ArrayList<T>::push_back(ArrayList<T>::value_type&& value)
{
  if (mySize != myCapacity)
  {
    new (myData + mySize) T(std::move(value));
    ++mySize;
    return;
  }
  
  size_type nextCapacity = 
    (myCapacity != 0) ? myCapacity * GROWTH_FACTOR : INITIAL_MIN_CAPACITY;
  reallocateCapacity(nextCapacity);

  new (myData + mySize) T(std::move(value));
  ++mySize;

  return;
}

template <class T>
void ArrayList<T>::swap(ArrayList<T>& other) noexcept
{
  std::swap(myData, other.myData);
  std::swap(mySize, other.mySize);
  std::swap(myCapacity, other.myCapacity);

  return;
}

template <class T>
void ArrayList<T>::clear() noexcept
{
  if (mySize != 0) {
    deleteRange(myData, myData + mySize);
  }
  mySize = 0;

  return;
}

template <class T>
bool operator==(const ArrayList<T>& lhs, const ArrayList<T>& rhs)
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
bool operator!=(const ArrayList<T>& lhs, const ArrayList<T>& rhs)
{
  return !(lhs == rhs);
}

template <class T>
void swap(ArrayList<T>& lhs, ArrayList<T>& rhs) noexcept
{
  lhs.swap(rhs);
}
