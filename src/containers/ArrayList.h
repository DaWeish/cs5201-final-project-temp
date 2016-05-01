////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   ArrayList.h
// brief  Implementation of the ArrayList ADT, parameterized for easy use.
////////////////////////////////////////////////////////////////////////////////
//
// Note this file is not used for this assignment and does not have correct
// commenting.

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstddef>

template <class T>
class ArrayList
{
  public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::size_t size_type;

    constexpr static auto INITIAL_MIN_CAPACITY = 8;
    constexpr static auto GROWTH_FACTOR = 2;

    ArrayList();
    explicit ArrayList(size_type size);
    ArrayList(const ArrayList& other);
    ArrayList(ArrayList&& other);
    ~ArrayList();

    value_type& operator[](size_type index);
    const value_type& operator[](size_type index) const;

    ArrayList& operator=(ArrayList other) noexcept;

    value_type& at(size_type index);
    const value_type& at(size_type index) const;

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    size_type size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;

    void resize(size_type size);
    void resize(size_type size, const value_type& value);

    void push_back(const value_type& value);
    void push_back(value_type&& value);


    void swap(ArrayList& other) noexcept;
    void clear() noexcept;

  private:
    size_type mySize;
    size_type myCapacity;
    T* myData;

    // Request size using malloc for holding size elements of T
    static pointer allocateSize(size_type size);
    // Copy values from begin to end to target, memory must be allocated first
    static void copyRange(pointer begin, pointer end, pointer target);
    // deletes the values from begin to end by calling destructor
    static void deleteRange(pointer begin, pointer end);
    // call default constructor to create objects from begin to end
    static void constructRange(pointer begin, pointer end);
    static void constructRange(pointer begin, pointer end, const value_type& value);
    // allocates new data, copies values, then swaps with current data
    void reallocateCapacity(size_type capacity);
};

template <class T>
bool operator==(const ArrayList<T>& lhs, const ArrayList<T>& rhs);

template <class T>
bool operator!=(const ArrayList<T>& lhs, const ArrayList<T>& rhs);

template <class T>
void swap(ArrayList<T>& lhs, ArrayList<T>& rhs) noexcept;

#include "ArrayList.hpp"

#endif
