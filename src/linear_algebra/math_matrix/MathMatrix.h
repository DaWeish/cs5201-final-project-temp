/*
 * Connor Walsh
 * MathMatrix.h : Standard Math Matrix following the IMathMatrix interface
 */

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "../../containers/Array.h"
#include "../MathVector.h"
#include "BaseMathMatrix.h"
#include "IMathMatrix.h"

template <class T>
class MathMatrix : public BaseMathMatrix<T, MathMatrix>
{
  public:

    MathMatrix() : myColumns(0) {}
    MathMatrix(size_t rows, size_t cols);
    MathMatrix(const MathMatrix& other);
    MathMatrix(MathMatrix&& other);
    ~MathMatrix();

    MathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    MathMatrix<T>& operator=(MathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;

    MathMatrix<T>& opPlusEquals(const IMathMatrix<T>& rhs);
    MathMatrix<T>& opMinusEquals(const IMathMatrix<T>& rhs);

    MathMatrix<T>& opTimesEquals(const T& scaler);

    MathMatrix<T>* opPlus(const IMathMatrix<T>& rhs) const;
    MathMatrix<T>* opMinus(const IMathMatrix<T>& rhs) const;
    MathMatrix<T>* opMinus() const;
    MathMatrix<T>* opTimes(const IMathMatrix<T>& rhs) const;
    MathMatrix<T>* opTimes(const T& scaler) const;

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
    void swap(MathMatrix& other);

    Array<MathVector<T>*> myRows;
    int myColumns;
    constexpr static int DEFAULT_SIZE = 2;
};

#include "MathMatrix.hpp"

#endif
