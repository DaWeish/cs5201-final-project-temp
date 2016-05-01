////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   Array.h
// brief  A simple class to represent an array with a construction time size.
//        Allows for copying from other arrays and can throw exceptions for
//        use of the at function with illegal indices
////////////////////////////////////////////////////////////////////////////////

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

////////////////////////////////////////////////////////////////////////////////
// class Array
// brief This class represents a simple array. It is created with a specific size
// but can take on a new size when the = operator is used
////////////////////////////////////////////////////////////////////////////////
template <class T>
class Array
{
  public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::size_t size_type;

////////////////////////////////////////////////////////////////////////////////
// fn Default Constructor
// brief Constructs a default Array object
// post Array represents a zero length array and provides almost no functionality
////////////////////////////////////////////////////////////////////////////////
    Array();

////////////////////////////////////////////////////////////////////////////////
// fn Size Constructor
// brief Creates an Array of size with default construction of elements T()
// pre size must be non-negative otherwise it will become a large postive number
//    due to its type being size_type
// post Array is of size and contains T[size] elements with default Construction
////////////////////////////////////////////////////////////////////////////////
    explicit Array(size_type size);

////////////////////////////////////////////////////////////////////////////////
// fn Copy Constructor
// brief Creates a copy of the passed in Array
// post this now contains a copy of the elements in other
////////////////////////////////////////////////////////////////////////////////
    Array(const Array& other);

////////////////////////////////////////////////////////////////////////////////
// fn Move Constructor
// brief Creates an Array by moving the elements from passed in Rvalue ref
// post this now contains the moved data from other and other's data is set
//    to nullptr
////////////////////////////////////////////////////////////////////////////////
    Array(Array&& other);

////////////////////////////////////////////////////////////////////////////////
// fn Destructor
// brief Deletes the Array
// post myData now contains a nullptr and all elements T[] are destructed using
//    delete[]
////////////////////////////////////////////////////////////////////////////////
    ~Array();

////////////////////////////////////////////////////////////////////////////////
// fn operator[] (const)
// brief returns a reference to the data element at index
// pre Index should be less than size otherwise behaivior is undefined
// post the value requested by index is returned by reference
////////////////////////////////////////////////////////////////////////////////
    value_type& operator[](size_type index);
    const value_type& operator[](size_type index) const;

////////////////////////////////////////////////////////////////////////////////
// fn operator=
// brief sets this's data equal to a copy of other's data
// post this now contains a copy of the elements in other and returns this by
//    retference
////////////////////////////////////////////////////////////////////////////////
    Array& operator=(Array other) noexcept;

////////////////////////////////////////////////////////////////////////////////
// fn begin()/end() (const)
// brief returns an (const) iterator to the beginning/end of myData
// pre this's size should be greater than zero otherwise a nullptr is returned
//    and cannot be dereferenced
// post returns copy of (const) iterator to beginning/end of data
////////////////////////////////////////////////////////////////////////////////
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

////////////////////////////////////////////////////////////////////////////////
// fn at (const)
// brief returns the element indexed by index
// pre index should be a valid element index otherwise an out_of_bounds exception
//    is thrown
// post returns a (const) reference to the element at index
////////////////////////////////////////////////////////////////////////////////
    value_type& at(size_type index);
    const value_type& at(size_type index) const;

////////////////////////////////////////////////////////////////////////////////
// fn size
// brief returns the size of the Array
// post returns the size of the Array by value
////////////////////////////////////////////////////////////////////////////////
    size_type size() const noexcept;

////////////////////////////////////////////////////////////////////////////////
// fn swap
// brief swaps the data elements of this with other
// post this now contains other's data and other now contains this's data
//    the sizes are also swapped to make sure of integrity
////////////////////////////////////////////////////////////////////////////////
    void swap(Array& other) noexcept;

  private:
    size_type mySize;
    T* myData;
};

#include "Array.hpp"

#endif
