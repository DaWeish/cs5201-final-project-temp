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
    UpTriangleMathMatrix(size_t rows, size_t cols);
    UpTriangleMathMatrix(const UpTriangleMathMatrix& other);
    UpTriangleMathMatrix(UpTriangleMathMatrix&& other);
    ~UpTriangleMathMatrix();

    UpTriangleMathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix<T>& operator=(UpTriangleMathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;

    UpTriangleMathMatrix<T>& opPlusEquals(const IMathMatrix<T>& rhs);
    UpTriangleMathMatrix<T>& opMinusEquals(const IMathMatrix<T>& rhs);

    UpTriangleMathMatrix<T>& opTimesEquals(const T& scaler);

    MathMatrix<T>* opPlus(const IMathMatrix<T>& rhs) const;
    MathMatrix<T>* opMinus(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix<T>* opMinus() const;
    MathMatrix<T>* opTimes(const IMathMatrix<T>& rhs) const;
    UpTriangleMathMatrix<T>* opTimes(const T& scaler) const;

    MathVector<T>& at(size_t index);
    const MathVector<T>& at(size_t index) const;
    T& at(size_t row, size_t column);
    const T& at(size_t row, size_t column) const;

    size_t getRows() const;
    size_t getCols() const;

    void swapRows(size_t row1, size_t row2);
    void printToStream(std::ostream& os) const;
    void readFromStream(std::istream& is);

  private:
    void swap(UpTriangleMathMatrix& other);

    Array<MathVector<T>*> myRows;
    const T zero = 0;
    int myColumns;
    constexpr static int DEFAULT_SIZE = 2;
};

#include "UpTriangleMathMatrix.hpp"

#endif
