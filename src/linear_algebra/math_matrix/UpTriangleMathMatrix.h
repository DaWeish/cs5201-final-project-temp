/*
 * Connor Walsh
 * UpTriangleMathMatrix.h : Upper Triangular Matrix Implementing the IMathMatrix
 *  Interface. 
 */

#ifndef UP_TRIANGLE_MATH_MATRIX_H
#define UP_TRIANGLE_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <memory>
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

    std::unique_ptr<IMathMatrix<T>> opPlus(const IMathMatrix<T>& rhs) const;
    std::unique_ptr<IMathMatrix<T>> opMinus(const IMathMatrix<T>& rhs) const;
    std::unique_ptr<IMathMatrix<T>> opMinus() const;
    std::unique_ptr<IMathMatrix<T>> opTimes(const IMathMatrix<T>& rhs) const;
    MathVector<T> opTimes(const MathVector<T> rhs) const;
    std::unique_ptr<IMathMatrix<T>> opTimes(const T& scaler) const;

    std::unique_ptr<IMathMatrix<T>> getTranspose() const;

    T& at(size_t row, size_t column);
    const T& at(size_t row, size_t column) const;

    size_t getRows() const;
    size_t getCols() const;

    void swapRows(size_t row1, size_t row2);
    void printToStream(std::ostream& os) const;
    void readFromStream(std::istream& is);
    void swap(UpTriangleMathMatrix& other);
  private:
    // TODO change this to an array of unique_ptrs
    Array<MathVector<T>*> myRows;
    size_t myColumns;
    const T zero = 0;
};

#include "UpTriangleMathMatrix.hpp"

#endif
