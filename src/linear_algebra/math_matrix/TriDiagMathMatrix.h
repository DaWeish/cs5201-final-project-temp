/*
 * Connor Walsh
 * TriDiagMathMatrix.h : Tridiagonal Math Matrix following the IMathMatrix interface
 */

#ifndef TRI_DIAG_MATH_MATRIX_H
#define TRI_DIAG_MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "BaseMathMatrix.h"
#include "IMathMatrix.h"

template <class T>
class TriDiagMathMatrix : public BaseMathMatrix<T, TriDiagMathMatrix>
{
  public:
    TriDiagMathMatrix() : myColumns(0) {}
    TriDiagMathMatrix(size_t rows, size_t cols);
    TriDiagMathMatrix(const TriDiagMathMatrix& other);
    TriDiagMathMatrix(TriDiagMathMatrix&& other);
    ~TriDiagMathMatrix();

    TriDiagMathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    TriDiagMathMatrix<T>& operator=(TriDiagMathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;

    TriDiagMathMatrix<T>& opPlusEquals(const IMathMatrix<T>& rhs);
    TriDiagMathMatrix<T>& opMinusEquals(const IMathMatrix<T>& rhs);

    TriDiagMathMatrix<T>& opTimesEquals(const T& scaler);

    TriDiagMathMatrix<T>* opPlus(const IMathMatrix<T>& rhs) const;
    TriDiagMathMatrix<T>* opMinus(const IMathMatrix<T>& rhs) const;
    TriDiagMathMatrix<T>* opMinus() const;
    TriDiagMathMatrix<T>* opTimes(const IMathMatrix<T>& rhs) const;
    TriDiagMathMatrix<T>* opTimes(const T& scaler) const;

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
    void swap(TriDiagMathMatrix& other);

    Array<MathVector<T>*> myRows;
    size_t myColumns;
};

#include "TriDiagMathMatrix.hpp"

#endif
