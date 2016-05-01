////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   MathVector.h
// brief  Class to represent a mathematical vector
////////////////////////////////////////////////////////////////////////////////

#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <iostream>
#include <cstddef>

#include "../containers/Array.h"

////////////////////////////////////////////////////////////////////////////////
// class MathVector
// brief Class to represent a mathematical vector with operations for addition,
//    subtraction, inner product, and scaler multiplication
////////////////////////////////////////////////////////////////////////////////
template <class T>
class MathVector;

////////////////////////////////////////////////////////////////////////////////
// fn operator+/-
// brief function for adding/subtracting two vectors together
// pre lhs and rhs must be of same length otherwise an exception is thrown
//    T::operator+= must be defined and return type T
// post returns a copy of the result of lhs +/- rhs
////////////////////////////////////////////////////////////////////////////////
template <class T>
MathVector<T> operator+(MathVector<T> lhs, const MathVector<T>& rhs);
template <class T>
MathVector<T> operator-(MathVector<T> lhs, const MathVector<T>& rhs);

////////////////////////////////////////////////////////////////////////////////
// fn operator- (unary)
// brief function to negate all values of a vector
// pre T::operator-(unary) must be defined
// post returns a copy vector with all values multiplied by -1
////////////////////////////////////////////////////////////////////////////////
template <class T>
MathVector<T> operator-(MathVector<T> vector);

////////////////////////////////////////////////////////////////////////////////
// fn operator* (scalers)
// brief function for multiplying a vector by a scaler
// pre T::operator* must be defined and return type T
// post returns a copy of vector where all elements are multiplied by scaler
////////////////////////////////////////////////////////////////////////////////
template <class T>
MathVector<T> operator*(T scaler, MathVector<T> vector);
template <class T>
MathVector<T> operator*(MathVector<T> vector, T scaler);

////////////////////////////////////////////////////////////////////////////////
// fn operator* (dotProduct)
// brief function for computing a dot product between two vectors
// pre T::operator* and T::operator+ must be defined
//    lhs and rhs must be of the same length or an exception is thrown
// post returns a copy of result of lhs dotProduct rhs
////////////////////////////////////////////////////////////////////////////////
template <class T>
typename MathVector<T>::value_type operator*(const MathVector<T>& lhs, const MathVector<T>& rhs);

////////////////////////////////////////////////////////////////////////////////
// fn operator==/!=
// brief equality/inequality operator for two vectors
// post returns true/false if both vectors have the same/different sizes and/or
//    all/one of their elements are the same/different
////////////////////////////////////////////////////////////////////////////////
template <class T>
bool operator==(const MathVector<T>& lhs, const MathVector<T>& rhs);
template <class T>
bool operator!=(const MathVector<T>& lhs, const MathVector<T>& rhs);

////////////////////////////////////////////////////////////////////////////////
// fn operator<<
// brief allows a vector to be output to a stream
// pre T::operator<< must be defined
// post os contains the result of putting rhs on the stream and is returned
//    by reference
////////////////////////////////////////////////////////////////////////////////
template <class T>
std::ostream& operator<<(std::ostream& os, const MathVector<T>& rhs);

////////////////////////////////////////////////////////////////////////////////
// fn operator>>
// brief allows a vector to be read from a stream
// pre is must contain a valid vector representation of size equal to rhs.size()
//    otherwise an exception will be thrown
// post the vector representation is removed from stream is and rhs now holds
//    members representing said vector
////////////////////////////////////////////////////////////////////////////////
template <class T>
std::istream& operator>>(std::istream& is, MathVector<T>& rhs);

template <class T>
class MathVector
{
  private:
    Array<T> myValues;

  public:
    typedef typename Array<T>::size_type size_type;
    typedef typename Array<T>::value_type value_type;
    typedef typename Array<T>::iterator iterator;
    typedef typename Array<T>::const_iterator const_iterator;

    ////////////////////////////////////////////////////////////////////////////////
    // fn Default Constructor
    // brief contrsuts a default vector object
    // post this contains a vector of size 0
    ////////////////////////////////////////////////////////////////////////////////
    MathVector();

    ////////////////////////////////////////////////////////////////////////////////
    // fn Size Constructor
    // brief Creates a MathVector with size
    // pre Size should be positive otherwise the unsigned type will make a negative
    //    into a positive number and results will be unexpected
    // post this contains size elements with default Construction
    ////////////////////////////////////////////////////////////////////////////////
    explicit MathVector(size_type size);

    ////////////////////////////////////////////////////////////////////////////////
    // fn Copy Constructor
    // brief Creates a MathVector which is a copy of another MathVector
    // post this contains a copy of all elements of other
    ////////////////////////////////////////////////////////////////////////////////
    MathVector(const MathVector& other);

    ////////////////////////////////////////////////////////////////////////////////
    // fn Conversion from Array
    // brief Constructs a MathVector from an Array object
    // post this now contains a copy of all elements in other
    ////////////////////////////////////////////////////////////////////////////////
    MathVector(const Array<T>& other);

    ////////////////////////////////////////////////////////////////////////////////
    // fn Move Constructor
    // brief Constructs a MathVector by moving data from other
    // post other is now swapped with this therefore this contains the data that other
    //    held previously
    ////////////////////////////////////////////////////////////////////////////////
    MathVector(MathVector&& other);
    MathVector(Array<T>&& other);

    ~MathVector(); // Default Destructor

    ////////////////////////////////////////////////////////////////////////////////
    // fn begin/end (const)
    // brief used to get an iterator to beginning/end of vector
    // pre if MathVector has size 0, begin/end will be nullptr and should not be
    //    dereferenced
    // post returns a copy of an iterator to the beginning/end of the vector
    ////////////////////////////////////////////////////////////////////////////////
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    MathVector& operator+=(const MathVector& other);
    MathVector& operator-=(const MathVector& other);

    MathVector& operator*=(value_type scaler);

    friend bool operator==<T>(const MathVector& lhs, const MathVector& rhs);
    friend bool operator!=<T>(const MathVector& lhs, const MathVector& rhs);

    ////////////////////////////////////////////////////////////////////////////////
    // fn operator[] (const)
    // brief returns a reference to the element requested by index
    // pre index should be a valid element otherwise an exception is thrown
    // post returns the requested element by (const) reference
    ////////////////////////////////////////////////////////////////////////////////
    value_type& operator[](size_type index);
    const value_type& operator[](size_type index) const;

    MathVector& operator=(MathVector other) noexcept;

    ////////////////////////////////////////////////////////////////////////////////
    // fn dotProduct
    // brief calculates the dotProduct between this an other
    // pre other must have the same size as this else exception is thrown
    //    T::operator* and T::operator + must be defined 
    // post returns a copy of the result of the dotproduct
    ////////////////////////////////////////////////////////////////////////////////
    value_type dotProduct(const MathVector& other) const;

    ////////////////////////////////////////////////////////////////////////////////
    // fn getMagnitude
    // brief gets the measure of this vector
    // pre T::operator* and T::operator+ must be defined
    // post returns the magnitude of this vector sqr(this dotProduct this)
    ////////////////////////////////////////////////////////////////////////////////
    value_type getMagnitude() const;

    ////////////////////////////////////////////////////////////////////////////////
    // fn size
    // brief returns the size/length of this vector
    // post returns copy of the size of the underlying Array
    ////////////////////////////////////////////////////////////////////////////////
    size_type size() const noexcept;

    ////////////////////////////////////////////////////////////////////////////////
    // fn zero
    // brief zeros out this vector
    // pre T must be assignable to 0
    // post all values are assigned to zero in this
    ////////////////////////////////////////////////////////////////////////////////
    void zero() noexcept;
};

#include "MathVector.hpp"

#endif
