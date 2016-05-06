////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   GaussianEliminationSolverTest.h 
// brief  Class to represent a set of unit tests for GaussianElmination
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "gtest/gtest.h"

#include "../linear_algebra/matrix_solver/GaussianEliminationSolver.h"
#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"
#include "../linear_algebra/math_matrix/IMathMatrix.h"

class GaussianEliminationSolverTest : public ::testing::Test {
};

TEST_F(GaussianEliminationSolverTest, AugmentedMatrix)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  MathVector<double> vector(2);
  vector[0] = 5;
  vector[1] = 6;

  MathMatrix<double> augmented(2, 3);
  augmented(0, 0) = 1;
  augmented(0, 1) = 2;
  augmented(0, 2) = 5;
  augmented(1, 0) = 3;
  augmented(1, 1) = 4;
  augmented(1, 2) = 6;

  MathMatrix<double> result = GaussianEliminationSolver<double>::augmentedMatrix
    (matrix1, vector);

  EXPECT_TRUE(augmented == result);
}

TEST_F(GaussianEliminationSolverTest, ForwardElimination)
{
  MathMatrix<double> augmented(2, 3);
  augmented(0, 0) = 1;
  augmented(0, 1) = 2;
  augmented(0, 2) = 1;
  augmented(1, 0) = 1;
  augmented(1, 1) = 1;
  augmented(1, 2) = 2;

  MathMatrix<double> result(2, 3);
  result(0, 0) = 1;
  result(0, 1) = 2;
  result(0, 2) = 1;
  result(1, 0) = 1;
  result(1, 1) = -1;
  result(1, 2) = 1;

  EXPECT_TRUE(result == GaussianEliminationSolver<double>::forwardElimination
      (augmented));
}

TEST_F(GaussianEliminationSolverTest, BackSubstitution)
{
  MathMatrix<double> augmented(2, 3);
  augmented(0, 0) = 1;
  augmented(0, 1) = 2;
  augmented(0, 2) = 1;
  augmented(1, 0) = 1;
  augmented(1, 1) = 1;
  augmented(1, 2) = 2;

  MathMatrix<double> forward = GaussianEliminationSolver<double>::forwardElimination
    (augmented);

  MathVector<double> backward = GaussianEliminationSolver<double>::backSubstitution
    (forward);
  EXPECT_EQ(3, backward[0]);
  EXPECT_EQ(-1, backward[1]);
}

TEST_F(GaussianEliminationSolverTest, FunctionOperator)
{
  GaussianEliminationSolver<double> gauss;

  MathMatrix<double> coeff(2, 2);
  coeff(0, 0) = 1;
  coeff(0, 1) = 2;
  coeff(1, 0) = 1;
  coeff(1, 1) = 1;

  MathVector<double> constants(2);
  constants[0] = 1;
  constants[1] = 2;

  MathVector<double> result(2);
  result[0] = 3;
  result[1] = -1;

  EXPECT_EQ(result, gauss(coeff, constants));

  gauss.setUsePivot(true);

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

  EXPECT_EQ(answer, gauss(A, b));
}
