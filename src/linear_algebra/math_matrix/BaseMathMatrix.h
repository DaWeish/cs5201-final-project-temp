/*
 * Connor Walsh
 * BaseMathMatrix.h : CRTP Base for MathMatrix interface
 *
 * This class simply forwards the polymorphic interface functions onto the
 * appropriate Derived implementation function
 */

#ifndef BASE_MATH_MATRIX_H
#define BASE_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "IMathMatrix.h"

template <class T, template <class> class Derived>
class BaseMathMatrix : public IMathMatrix<T> {
  public:
    virtual IMathMatrix<T>& operator=(const IMathMatrix<T>& rhs)
    {
      return static_cast<Derived<T>*>(this)->opAssign(rhs);
    }

    virtual bool operator==(const IMathMatrix<T>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->opEquality(rhs);
    }

    virtual bool operator!=(const IMathMatrix<T>& rhs) const
    {
      return !operator==(rhs);
    }

    virtual IMathMatrix<T>& operator+=(const IMathMatrix<T>& rhs)
    {
      return static_cast<Derived<T>*>(this)->opPlusEquals(rhs);
    }

    virtual IMathMatrix<T>& operator-=(const IMathMatrix<T>& rhs)
    {
      return static_cast<Derived<T>*>(this)->opMinusEquals(rhs);
    }

    virtual IMathMatrix<T>& operator*=(const T& scaler)
    {
      return static_cast<Derived<T>*>(this)->opTimesEquals(scaler);
    }

    virtual IMathMatrix<T>* operator+(const IMathMatrix<T>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->opPlus(rhs);
    }

    virtual IMathMatrix<T>* operator-(const IMathMatrix<T>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->opMinus(rhs);
    }

    virtual IMathMatrix<T>* operator-() const
    {
      return static_cast<const Derived<T>*>(this)->opMinus();
    }

    virtual IMathMatrix<T>* operator*(const IMathMatrix<T>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->opTimes(rhs);
    }

    virtual IMathMatrix<T>* operator*(const T& scaler) const
    {
      return static_cast<const Derived<T>*>(this)->opTimes(scaler);
    }

    virtual MathVector<T>& operator[](size_t index)
    {
      return static_cast<Derived<T>*>(this)->at(index);
    }

    virtual const MathVector<T>& operator[](size_t index) const
    {
      return static_cast<const Derived<T>*>(this)->at(index);
    }

    // This is the multidimensional index operator for a matrix
    virtual T& operator()(size_t row, size_t column)
    {
      return static_cast<Derived<T>*>(this)->at(row, column);
    }

    virtual const T& operator()(size_t row, size_t column) const
    {
      return static_cast<const Derived<T>*>(this)->at(row, column);
    }

    virtual size_t rows() const
    {
      return static_cast<const Derived<T>*>(this)->getRows();
    }

    virtual size_t cols() const
    {
      return static_cast<const Derived<T>*>(this)->getCols();
    }

    virtual void swap(size_t row1, size_t row2)
    {
      static_cast<Derived<T>*>(this)->swapRows(row1, row2);
    }

    virtual void print(std::ostream& os) const
    {
      static_cast<const Derived<T>*>(this)->printToStream(os);
    }

    virtual void read(std::istream& is)
    {
      static_cast<Derived<T>*>(this)->readFromStream(is);
    }

    virtual IMathMatrix<T>* clone()
    {
      return new Derived<T>(static_cast<const Derived<T>&>(*this));
    }
};

#endif
