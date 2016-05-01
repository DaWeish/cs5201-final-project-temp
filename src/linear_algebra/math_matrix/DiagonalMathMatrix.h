/*
 * Connor Walsh
 * DiagonalMathMatrix.h : Standard Math Matrix following the IMathMatrix interface
 */

#ifndef DIAGONAL_MATH_MATRIX_H
#define DIAGONAL_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "../../containers/Array.h"
#include "../MathVector.h"
#include "BaseMathMatrix.h"
#include "IMathMatrix.h"
#include "MathMatrix.h"

template <class T>
class DiagonalMathMatrix : public BaseMathMatrix<T, DiagonalMathMatrix>
{
  public:

    DiagonalMathMatrix() : myRows(0), myColumns(0) {}
    DiagonalMathMatrix(size_t rows, size_t cols);
    DiagonalMathMatrix(const DiagonalMathMatrix& other);
    DiagonalMathMatrix(DiagonalMathMatrix&& other);
    ~DiagonalMathMatrix();

    DiagonalMathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    DiagonalMathMatrix<T>& operator=(DiagonalMathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;

    DiagonalMathMatrix<T>& opPlusEquals(const IMathMatrix<T>& rhs);
    DiagonalMathMatrix<T>& opMinusEquals(const IMathMatrix<T>& rhs);

    DiagonalMathMatrix<T>& opTimesEquals(const T& scaler);

    MathMatrix<T>* opPlus(const IMathMatrix<T>& rhs) const;
    MathMatrix<T>* opMinus(const IMathMatrix<T>& rhs) const;
    DiagonalMathMatrix<T>* opMinus() const;
    MathMatrix<T>* opTimes(const IMathMatrix<T>& rhs) const;
    DiagonalMathMatrix<T>* opTimes(const T& scaler) const;

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
    void swap(DiagonalMathMatrix& other);

    MathVector<T>* myDiagonal;
    int myRows;
    int myColumns;
    const T zero = 0;
    constexpr static int DEFAULT_SIZE = 2;
};

#include "DiagonalMathMatrix.hpp"

#endif
