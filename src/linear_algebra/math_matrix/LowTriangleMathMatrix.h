/*
 * Connor Walsh
 * LowTriangleMathMatrix.h : Lower Triangular Matrix Implementing the IMathMatrix
 *  Interface. 
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

template <class T>
class LowTriangleMathMatrix : public BaseMathMatrix<T, LowTriangleMathMatrix>
{
  public:

    LowTriangleMathMatrix() : myColumns(0) {}
    LowTriangleMathMatrix(size_t rows, size_t cols);
    LowTriangleMathMatrix(const LowTriangleMathMatrix& other);
    LowTriangleMathMatrix(LowTriangleMathMatrix&& other);
    ~LowTriangleMathMatrix();

    LowTriangleMathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    LowTriangleMathMatrix<T>& operator=(LowTriangleMathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;

    LowTriangleMathMatrix<T>& opPlusEquals(const IMathMatrix<T>& rhs);
    LowTriangleMathMatrix<T>& opMinusEquals(const IMathMatrix<T>& rhs);

    LowTriangleMathMatrix<T>& opTimesEquals(const T& scaler);

    MathMatrix<T>* opPlus(const IMathMatrix<T>& rhs) const;
    MathMatrix<T>* opMinus(const IMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix<T>* opMinus() const;
    MathMatrix<T>* opTimes(const IMathMatrix<T>& rhs) const;
    LowTriangleMathMatrix<T>* opTimes(const T& scaler) const;

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
    void swap(LowTriangleMathMatrix& other);

    Array<MathVector<T>*> myRows;
    int myColumns;
    const T zero = 0;
    constexpr static int DEFAULT_SIZE = 2;
};

#include "LowTriangleMathMatrix.hpp"

#endif
