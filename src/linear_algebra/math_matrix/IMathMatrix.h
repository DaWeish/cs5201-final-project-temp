/*
 * Connor Walsh
 * IMathMatrix.h : Interface for a Mathematical Matrix class
 */

#ifndef I_MATH_MATRIX_H
#define I_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "../MathVector.h"

template <class T>
class IMathMatrix
{
  public:
    virtual ~IMathMatrix() {};

    virtual IMathMatrix<T>& operator=(const IMathMatrix<T>& rhs) = 0;

    virtual bool operator==(const IMathMatrix<T>& rhs) const = 0;
    virtual bool operator!=(const IMathMatrix<T>& rhs) const = 0;

    virtual IMathMatrix<T>& operator+=(const IMathMatrix<T>& rhs) = 0;
    virtual IMathMatrix<T>& operator-=(const IMathMatrix<T>& rhs) = 0;

    virtual IMathMatrix<T>& operator*=(const T& scaler) = 0;

    virtual IMathMatrix<T>* operator+(const IMathMatrix<T>& rhs) const = 0;
    virtual IMathMatrix<T>* operator-(const IMathMatrix<T>& rhs) const = 0;
    virtual IMathMatrix<T>* operator-() const = 0;
    virtual IMathMatrix<T>* operator*(const IMathMatrix<T>& rhs) const = 0;
    virtual IMathMatrix<T>* operator*(const T& scaler) const = 0;

    virtual MathVector<T>& operator[](size_t index) = 0;
    virtual const MathVector<T>& operator[](size_t index) const = 0;

    virtual T& operator()(size_t row, size_t column) = 0;
    virtual const T& operator()(size_t row, size_t column) const = 0;

    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;

    virtual void swap(size_t row1, size_t row2) = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual IMathMatrix<T>* clone() = 0; 
};

template <class T>
IMathMatrix<T>* operator*(const T& scaler, const IMathMatrix<T>& rhs)
{
  return rhs * scaler;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const IMathMatrix<T>& rhs)
{
  rhs.print(os);
  return os;
}

template <class T>
std::istream& operator>>(std::istream& is, IMathMatrix<T>& rhs)
{
  rhs.read(is);
  return is;
}

#endif
