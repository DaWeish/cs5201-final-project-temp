/*
 * author Connor Walsh
 * file   QRSolver.h
 * brief  This class implements the Matrix Solver interface using the QR method
 */

#ifndef QR_SOLVER_H
#define QR_SOLVER_H

#include <vector>
#include <stdexcept>
#include <iostream>

#include "IMatrixSolver.h"
#include "GaussianEliminationSolver.h"
#include "../MathVector.h"
#include "../math_matrix/IMathMatrix.h"
#include "../math_matrix/MathMatrix.h"
#include "../math_matrix/UpTriangleMathMatrix.h"
#include "../math_matrix/LowTriangleMathMatrix.h"

/*
 * class QRSolver
 * brief  This class implements the IMatrixSolver Interface and solves a 
 *        matrix equation using QR decomposition and back substitution
 */
template <class T>
class QRSolver : public IMatrixSolver<T>
{
  public:
    /*
     * brief  This function performs the QR method for calculating the eigen
     *        vector of a matrix
     * pre    A, Q, and R must have the same dimensions and T must have standard
     *        mathematical operations defined
     * post   A, Q, and R are changed and A holds the eigen values along
     *        the diagonal if the number of iterations caused it to converge
     */
    static void QRMethod(MathMatrix<T>& A, MathMatrix<T>& Q, 
        UpTriangleMathMatrix<T>& R, int numIter);

    /*
     * brief  This function performs QR decompostion on a matrix A
     * pre    A, Q, and R must be the same size and T must have standard
     *        mathematical operations defined
     * post   Q is an orthogonal matrix and R is upper triangular where
     *        A = QR
     */
    static void QRDecomposition(const MathMatrix<T>& A, MathMatrix<T>& Q,
        UpTriangleMathMatrix<T>& R);

    /*
     * brief  This operator runs the QR Decomposition algorithm and solves
     *        for x using Rx = Q^T*b
     * pre    A and b are of compatible dimensions and represent a matrix
     *        equation to solve of the form Ax = b
     * post   returns a MathVector equal to the solution x or throws an exception
     *        if a divide by zero is encountered
     */
    virtual MathVector<T> operator()
      (const IMathMatrix<T>& A, const MathVector<T>& b) const;
};

#include "QRSolver.hpp"

#endif
