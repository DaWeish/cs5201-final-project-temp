/*
 * Connor Walsh
 * IMathMatrixSolver.h : This file defines an interface used to solve matrix
 *  equations of the form Ax = b.
 */

#ifndef I_MATRIX_SOLVER_H
#define I_MATRIX_SOLVER_H

#pragma once

#include "../MathVector.h"
#include "../math_matrix/IMathMatrix.h"

template <class T>
class IMatrixSolver
{
  public:
    virtual MathVector<T> operator()
      (const IMathMatrix<T>& A, const MathVector<T>& b) const = 0;
};

#endif

