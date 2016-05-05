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

template <class T>
class UpTriangleMathMatrix : public BaseMathMatrix<T, UpTriangleMathMatrix>
{
  public:
    UpTriangleMathMatrix() : myColumns(0) {}
    explicit UpTriangleMathMatrix(size_t rows, size_t cols = 1);
    UpTriangleMathMatrix(const UpTriangleMathMatrix& other);
    UpTriangleMathMatrix(const IMathMatrix<T>& other);
    UpTriangleMathMatrix(UpTriangleMathMatrix&& other);
    ~UpTriangleMathMatrix();

    UpTriangleMathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix<T>& operator=(UpTriangleMathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;
    bool operator==(const UpTriangleMathMatrix& rhs) const;
    bool operator!=(const UpTriangleMathMatrix& rhs) const;

    UpTriangleMathMatrix& operator+=(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix& operator-=(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix& operator*=(const T& scaler);

    UpTriangleMathMatrix operator+(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix operator-(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix operator-() const;
    UpTriangleMathMatrix operator*(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix operator*(const T& scaler) const;
    MathVector<T> operator*(const MathVector<T>& rhs) const;

    UpTriangleMathMatrix transpose() const;
    UpTriangleMathMatrix swapRows(size_t row1, size_t row2);

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
