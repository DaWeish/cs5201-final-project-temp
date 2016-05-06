/*
 * Connor Walsh
 * UpTriangleMathMatrix.h : Upper Triangular Matrix Implementing the IMathMatrix
 *  Interface. 
 */

#ifndef UP_TRIANGLE_MATH_MATRIX_H
#define UP_TRIANGLE_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "../../containers/Array.h"
#include "../MathVector.h"
#include "BaseMathMatrix.h"
#include "IMathMatrix.h"
#include "MathMatrix.h"
#include "LowTriangleMathMatrix.h"

template <class T>
class UpTriangleMathMatrix : public BaseMathMatrix<T, UpTriangleMathMatrix>
{
  public:
    UpTriangleMathMatrix() : myColumns(0) {}
    explicit UpTriangleMathMatrix(size_t rows, size_t cols = 1);
    UpTriangleMathMatrix(const UpTriangleMathMatrix& other);
    explicit UpTriangleMathMatrix(const IMathMatrix<T>& other);
    UpTriangleMathMatrix(UpTriangleMathMatrix&& other);
    ~UpTriangleMathMatrix();

    using IMathMatrix<T>::operator=;
    UpTriangleMathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix<T>& operator=(UpTriangleMathMatrix rhs);

    using IMathMatrix<T>::operator==;
    using IMathMatrix<T>::operator!=;
    bool opEquality(const IMathMatrix<T>& rhs) const;
    bool operator==(const UpTriangleMathMatrix& rhs) const;
    bool operator!=(const UpTriangleMathMatrix& rhs) const;

    UpTriangleMathMatrix& opPlusEquals(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix& opMinusEquals(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix& opTimesEquals(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix& opTimesEquals(const T& scaler);

    MathMatrix<T> operator+(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix<T> operator+(const UpTriangleMathMatrix<T>& rhs) const;
    MathMatrix<T> operator-(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix<T> operator-(const UpTriangleMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix operator-() const;
    MathMatrix<T> operator*(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix operator*(const UpTriangleMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix operator*(const T& scaler) const;
    MathVector<T> operator*(const MathVector<T>& rhs) const;

//    LowTriangleMathMatrix<T> transpose() const;

    T& at(size_t row, size_t column);
    const T& at(size_t row, size_t column) const;

    size_t getRows() const;
    size_t getCols() const;

    void swap(UpTriangleMathMatrix& other);
    void printToStream(std::ostream& os) const;
    void readFromStream(std::istream& is);

  private:
    Array<MathVector<T>*> myRows;
    const T zero = 0;
    size_t myColumns;
};

#include "UpTriangleMathMatrix.hpp"

#endif
