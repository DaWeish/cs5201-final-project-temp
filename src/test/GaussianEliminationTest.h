////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   ArrayTest.h
// brief  Class to represent a set of unit tests for Array
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "gtest/gtest.h"

#include "../linear_algebra/GaussianEliminiation.h"
#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/MathMatrix2D.h"

class GaussianEliminationTest : public ::testing::Test {
};

TEST_F(GaussianEliminationTest, AugmentedMatrix)
{
  MathMatrix2D<int> matrix1(2, 2);
  matrix1[0][0] = 1;
  matrix1[0][1] = 2;
  matrix1[1][0] = 3;
  matrix1[1][1] = 4;

  MathVector<int> vector(2);
  vector[0] = 5;
  vector[1] = 6;

  MathMatrix2D<int> augmented(2, 3);
  augmented[0][0] = 1;
  augmented[0][1] = 2;
  augmented[0][2] = 5;
  augmented[1][0] = 3;
  augmented[1][1] = 4;
  augmented[1][2] = 6;

  EXPECT_TRUE(augmented == GaussianElimination<int>::augmentedMatrix(matrix1, vector));
}

TEST_F(GaussianEliminationTest, ForwardElimination)
{
  MathMatrix2D<int> augmented(2, 3);
  augmented[0][0] = 1;
  augmented[0][1] = 2;
  augmented[0][2] = 1;
  augmented[1][0] = 1;
  augmented[1][1] = 1;
  augmented[1][2] = 2;

  MathMatrix2D<int> result(2, 3);
  result[0][0] = 1;
  result[0][1] = 2;
  result[0][2] = 1;
  result[1][0] = 1;
  result[1][1] = -1;
  result[1][2] = 1;

  EXPECT_TRUE(result == GaussianElimination<int>::forwardElimination(augmented));
}

TEST_F(GaussianEliminationTest, BackSubstitution)
{
  MathMatrix2D<int> augmented(2, 3);
  augmented[0][0] = 1;
  augmented[0][1] = 2;
  augmented[0][2] = 1;
  augmented[1][0] = 1;
  augmented[1][1] = 1;
  augmented[1][2] = 2;

  MathMatrix2D<int> forward = GaussianElimination<int>::forwardElimination(augmented);

  MathMatrix2D<int> backward = GaussianElimination<int>::backSubstitution(forward);
  EXPECT_EQ(3, backward[0][2]);
  EXPECT_EQ(-1, backward[1][2]);
}

TEST_F(GaussianEliminationTest, FunctionOperator)
{
  GaussianElimination<int> gauss;

  MathMatrix2D<int> coeff(2, 2);
  coeff[0][0] = 1;
  coeff[0][1] = 2;
  coeff[1][0] = 1;
  coeff[1][1] = 1;

  MathVector<int> constants(2);
  constants[0] = 1;
  constants[1] = 2;

  MathVector<int> result(2);
  result[0] = 3;
  result[1] = -1;

  EXPECT_EQ(result, gauss(coeff, constants));
}
