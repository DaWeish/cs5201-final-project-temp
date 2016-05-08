/*
 * author Connor Walsh
 * brief  This class represents an array data structure which provides bounds
 *        checking and dynamic size creation
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

/*
 * class Array
 * brief This class represents a simple array. It is created with a specific size
 * but can take on a new size when the = operator is used
 */
template <class T>
class Array
{
  public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::size_t size_type;

    /*
     * brief  Constructs a default Array object
     * post   Array represents a zero length array and provides almost no 
     *        functionality
     */
    Array();

    /*
    * brief   Creates an Array of size with default construction of elements T()
    * pre     size must be non-negative
    * post    Array is of size and contains T[size] elements with default 
    *         Construction
    */
    explicit Array(size_type size);

    /*
    * brief   Creates a copy of the passed in Array
    * post    This now contains a copy of the elements in other
    */
    Array(const Array& other);

    /*
    * brief   Creates an Array by moving the elements from passed in Rvalue ref
    * post    This now contains the moved data from other and other's data is set
    *         to nullptr
    */
    Array(Array&& other);

    /*
    * brief   Deletes the Array
    * post    MyData now contains a nullptr and all elements T[] are 
    *         destructed using delete[]
    */
    ~Array();

    /*
    * brief   Returns a reference to the data element at index
    * pre     Index should be less than size otherwise behaivior is undefined
    * post    The value requested by index is returned by reference
    */
    value_type& operator[](size_type index);
    const value_type& operator[](size_type index) const;

    /*
    * brief   sets this's data equal to a copy of other's data
    * post    this now contains a copy of the elements in other and returns 
    *         this by reference
    */
    Array& operator=(Array other) noexcept;

    /*
    * brief   Returns an (const) iterator to the beginning/end of myData
    * pre     This's size should be greater than zero otherwise a nullptr is 
    *         returned and cannot be dereferenced
    * post    Returns copy of (const) iterator to beginning/end of data
    */
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    /*
    * brief   Returns the element indexed by index
    * pre     Index should be a valid element index otherwise an out_of_bounds 
    *         exception is thrown
    * post    Returns a (const) reference to the element at index
    */
    value_type& at(size_type index);
    const value_type& at(size_type index) const;

    /*
    * brief   Returns the size of the Array
    * post    Returns the size of the Array by value
    */
    size_type size() const noexcept;

    /*
    * brief   swaps the data elements of this with other
    * post    this now contains other's data and other now contains this's data
    *         the sizes are also swapped to make sure of integrity
    */
    void swap(Array& other) noexcept;

  private:
    size_type mySize;
    T* myData;
};

#include "Array.hpp"

#endif
