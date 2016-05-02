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
    explicit MathMatrix(size_t rows, size_t cols = 1);
    MathMatrix(const MathMatrix& other);
    MathMatrix(const IMathMatrix<T>& other);
    MathMatrix(MathMatrix&& other);
    ~MathMatrix();

    MathMatrix<T>& opAssign(const IMathMatrix<T>& rhs);
    MathMatrix<T>& operator=(MathMatrix rhs);

    bool opEquality(const IMathMatrix<T>& rhs) const;
    bool operator==(const MathMatrix& rhs) const;
    bool operator!=(const MathMatrix& rhs) const;

    MathMatrix& operator+=(const IMathMatrix<T>& rhs);
    MathMatrix& operator-=(const IMathMatrix<T>& rhs);
    MathMatrix& operator*=(const IMathMatrix<T>& rhs);
    MathMatrix& operator*=(const T& scaler);

    MathMatrix operator+(const IMathMatrix<T>& rhs) const;
    MathMatrix operator-(const IMathMatrix<T>& rhs) const;
    MathMatrix operator-() const;
    MathMatrix operator*(const IMathMatrix<T>& rhs) const;
    MathMatrix operator*(const T& scaler) const;
    MathVector<T> operator*(const MathVector<T>& rhs) const;

    MathMatrix transpose() const;
    MathMatrix swapRows(size_t row1, size_t row2);

    T& at(size_t row, size_t column);
    const T& at(size_t row, size_t column) const;

    size_t getRows() const;
    size_t getCols() const;

    void swap(MathMatrix& other);
    void printToStream(std::ostream& os) const;
    void readFromStream(std::istream& is);

  private:
    Array<MathVector<T>*> myRows;
    size_t myColumns;
};

template <class T>
MathMatrix<T> operator*(const T& scaler, MathMatrix<T> matrix)
{
  return matrix *= scaler;
}

#include "MathMatrix.hpp"

#endif
