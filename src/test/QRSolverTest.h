/*
 * author Connor Walsh
 * file   QRSolverTest.h
 * brief  Class to represent a set of unit tests for the QR Method
 */

#include <stdexcept>

#include "gtest/gtest.h"

#include "../linear_algebra/matrix_solver/QRSolver.h"
#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"
#include "../linear_algebra/math_matrix/IMathMatrix.h"

class QRSolverTest : public ::testing::Test {
};

TEST_F(QRSolverTest, QRDecomposition)
{
  MathMatrix<double> coeff(3, 3);
  coeff(0, 0) = 12;
  coeff(0, 1) = -51;
  coeff(0, 2) = 4;
  coeff(1, 0) = 6;
  coeff(1, 1) = 167;
  coeff(1, 2) = -68;
  coeff(2, 0) = -4;
  coeff(2, 1) = 24;
  coeff(2, 2) = -41;

  MathMatrix<double> Qoutput(3, 3);
  Qoutput(0, 0) = 6.0 / 7.0;
  Qoutput(0, 1) = (-69.0)/175.0;
  Qoutput(0, 2) = (-58.0)/175.0;
  Qoutput(1, 0) = 3.0/7.0;
  Qoutput(1, 1) = 158.0/175.0;
  Qoutput(1, 2) = 6.0/175.0;
  Qoutput(2, 0) = -2.0/7.0;
  Qoutput(2, 1) = 6.0/35.0;
  Qoutput(2, 2) = -33.0/35.0;

  UpTriangleMathMatrix<double> Routput(3, 3);
  Routput(0, 0) = 14;
  Routput(0, 1) = 21;
  Routput(0, 2) = -14;
  Routput(1, 1) = 175;
  Routput(1, 2) = -70;
  Routput(2, 2) = 35;


  MathMatrix<double> Q(3, 3);
  UpTriangleMathMatrix<double> R(3, 3);

  QRSolver<double>::QRDecomposition(coeff, Q, R);

//  std::cout << "Q after Decomp:\n" << Q << "\nExpected:\n" << Qoutput << std::endl;
//  std::cout << "R after Decomp:\n" << R << "\nExpected:\n" << Routput << std::endl;
}

TEST_F(QRSolverTest, EigenValues)
{
  MathMatrix<double> A(3, 3);
  A(0, 0) = -4;
  A(0, 1) = 14;
  A(0, 2) = 0;
  A(1, 0) = -5;
  A(1, 1) = 13;
  A(1, 2) = 0;
  A(2, 0) = -1;
  A(2, 1) = 0;
  A(2, 2) = 2;

  MathMatrix<double> Q(3, 3);
  UpTriangleMathMatrix<double> R(3, 3);

  QRSolver<double>::QRMethod(A, Q, R, 30);

//  std::cout << "A:\n" << A << std::endl;
//  std::cout << "Q:\n" << Q << std::endl;
//  std::cout << "R:\n" << R << std::endl;

  A(0, 0) = 2;
  A(0, 1) = 1;
  A(0, 2) = 0;
  A(1, 0) = 1;
  A(1, 1) = 3;
  A(1, 2) = 1;
  A(2, 0) = 0;
  A(2, 1) = 1;
  A(2, 2) = 4;

  QRSolver<double>::QRMethod(A, Q, R, 30);

//  std::cout << "A:\n" << A << std::endl;
//  std::cout << "Q:\n" << Q << std::endl;
//  std::cout << "R:\n" << R << std::endl;
}

TEST_F(QRSolverTest, FunctionOperator)
{
  QRSolver<double> solver;

  MathMatrix<double> coeff(2, 2);
  coeff(0, 0) = 1;
  coeff(0, 1) = 2;
  coeff(1, 0) = 3;
  coeff(1, 1) = -5;

  MathVector<double> constants(2);
  constants[0] = 4;
  constants[1] = 1;

  MathVector<double> result(2);
  result[0] = 2;
  result[1] = 1;

//  EXPECT_EQ(result, solver(coeff, constants));

  MathMatrix<double> Amatrix(3, 3);
  IMathMatrix<double>& A = Amatrix;
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 0) = 0;
  A(2, 1) = 0;
  A(2, 2) = 1;

  MathVector<double> b(3);
  b[0] = 3;
  b[1] = 1;
  b[2] = 1;

  MathVector<double> answer(3);
  answer[0] = 2;
  answer[1] = -1;
  answer[2] = 1;

  IMatrixSolver<double>& solverRef = solver;

  EXPECT_EQ(answer, solverRef(A, b));
}
