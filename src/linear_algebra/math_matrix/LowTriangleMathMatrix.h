/*
 * author Connor Walsh
 * file   LowTriangleMathMatrix.h 
 * brief  Lower Triangular Matrix Implementing the IMathMatrix
 *        Interface. 
 */

#ifndef LOW_TRIANGLE_MATH_MATRIX_H
#define LOW_TRIANGLE_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "../../containers/Array.h"
#include "../MathVector.h"
#include "BaseMathMatrix.h"
#include "IMathMatrix.h"
#include "MathMatrix.h"
#include "UpTriangleMathMatrix.h"

template <class T>
class UpTriangleMathMatrix;

template <class T>
class LowTriangleMathMatrix : public BaseMathMatrix<T, LowTriangleMathMatrix>
{
  public:
    LowTriangleMathMatrix() : myColumns(0) {}
    explicit LowTriangleMathMatrix(size_t rows, size_t cols = 1);
    LowTriangleMathMatrix(const LowTriangleMathMatrix& other);
    LowTriangleMathMatrix(const IMathMatrix<T>& other);
    LowTriangleMathMatrix(LowTriangleMathMatrix&& other);
    ~LowTriangleMathMatrix();

    LowTriangleMathMatrix<T>& operator=(LowTriangleMathMatrix rhs);

    using IMathMatrix<T>::operator==;
    using IMathMatrix<T>::operator!=;
    bool opEquality(const IMathMatrix<T>& rhs) const;
    bool operator==(const LowTriangleMathMatrix& rhs) const;
    bool operator!=(const LowTriangleMathMatrix& rhs) const;

    LowTriangleMathMatrix& opPlusEquals(const IMathMatrix<T>& rhs);
    LowTriangleMathMatrix& opMinusEquals(const IMathMatrix<T>& rhs);
    LowTriangleMathMatrix& opTimesEquals(const IMathMatrix<T>& rhs);
    LowTriangleMathMatrix& opTimesEquals(const T& scaler);

    MathMatrix<T> operator+(const IMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix<T> operator+(const LowTriangleMathMatrix<T>& rhs) const;
    MathMatrix<T> operator-(const IMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix<T> operator-(const LowTriangleMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix operator-() const;
    MathMatrix<T> operator*(const IMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix operator*(const LowTriangleMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix operator*(const T& scaler) const;
    MathVector<T> operator*(const MathVector<T>& rhs) const;

    UpTriangleMathMatrix<T> transpose() const;

    T& at(size_t row, size_t column);
    const T& at(size_t row, size_t column) const;

    size_t getRows() const;
    size_t getCols() const;

    void swap(LowTriangleMathMatrix& other);
    void printToStream(std::ostream& os) const;
    void readFromStream(std::istream& is);

  private:
    Array<MathVector<T>*> myRows;
    const T zero = 0;
    size_t myColumns;
};

#include "LowTriangleMathMatrix.hpp"

#endif
