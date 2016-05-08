/*
 * author Connor Walsh
 * file   GaussianEliminationSolver.h
 * brief  Class which implements the IMatrixSolver interface using Gaussian
 *        Elimination
 */

#ifndef GAUSSIAN_ELIMINATION_SOLVER_H
#define GAUSSIAN_ELIMINATION_SOLVER_H

#pragma once

#include <stdexcept>

#include "IMatrixSolver.h"
#include "../MathVector.h"
#include "../math_matrix/IMathMatrix.h"
#include "../math_matrix/MathMatrix.h"

/*
 * class  GaussianElminationSolver
 * brief  This class implements the IMatrixSolver interface using Gaussian
 *        Elimination techniques
 */
template <class T>
class GaussianEliminationSolver : public IMatrixSolver<T>
{
  bool usePivot = false;

  private:
    /*
     * brief  This function is used during pivoting to get the row index which
     *        is to be pivoted with the current row
     * pre    column must be a valid column index for matrix and same with row
     *        T must have the == and < operators defined
     * post   returns the row index of the row to swap with to achieve pivoting
     */
    static int getMaxColumnValueRow(const IMathMatrix<T>& matrix, int column,
        int startRow);

  public:
    /*
     * brief  Constructor taking a single parameter
     * post   Creates a GaussianEliminationSolver that uses pivoting or not
     *        based on input parameter
     */
    GaussianEliminationSolver(bool partialPivot = false) : usePivot(partialPivot) {}

    /*
     * brief  Function to change whether the pivoting technique is used
     * post   Solver will use piviting if true, and not if false
     */
    void setUsePivot(bool pivot) { usePivot = pivot; }

    /*
    * brief   This function operator performs the Gaussian elimination on a 
    *         given Matrix and constants. Can also perform partial pivoting
    * pre     coefficients and constants must be of compatible dimensions
    * post    returns the vector x in Ax = b where A = coefficients and
    *         b = constants
    */
    virtual MathVector<T> operator()
      (const IMathMatrix<T>& A, const MathVector<T>& b) const;

    /*
    * brief   This function creates an augmented matrix from a set of coefficients
    *         and a constants MathVector
    * pre     constants' size must be equal to coefficients.rows()
    * post    returns a matrix of size coefficients.rows() x 
    *         coefficients.columns() + 1 that is an augmented matrix of the inputs
    */
    static MathMatrix<T> augmentedMatrix(const IMathMatrix<T>& coefficients,
        const MathVector<T>& constants);

    /*
    * brief   Performs Gaussian forward elimination in place on an augmented
    *         IMathMatrix
    * pre     augmented must be a matrix that is of format created by
    *         member function augmentedMatrix
    * post    returns a new augmented matrix that is in eschelon form with the
    *         multipliers in the zero places
    */
    static MathMatrix<T> forwardElimination(const IMathMatrix<T>& augmented,
        bool usePartialPivot = false);

    /*
    * brief   Retrives the values represented by the forward elminiation matrix
    * pre     augmented is in echelon form
    * post    returns a new MathVector with the solutions to the equation Ax=b 
    *         represented by augmented
    */
    static MathVector<T> backSubstitution(const IMathMatrix<T>& augmented);
};

#include "GaussianEliminationSolver.hpp"

#endif
