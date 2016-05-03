////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   MathVectorTest.h
// brief  Class to represent a set of unit tests for MathMatrix's
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"

class MathMatrixTest : public ::testing::Test {};

TEST_F(MathMatrixTest, DefaultConstruction)
{
  MathMatrix<double> matrix1;

  EXPECT_EQ(0, matrix1.rows());
  EXPECT_EQ(0, matrix1.cols());
}

TEST_F(MathMatrixTest, SizeConstruction)
{
  MathMatrix<double> matrix1(4, 4);
  EXPECT_EQ(4, matrix1.rows());
  EXPECT_EQ(4, matrix1.cols());

  MathMatrix<double> matrix2(5, 7);
  EXPECT_EQ(5, matrix2.rows());
  EXPECT_EQ(7, matrix2.cols());
}

TEST_F(MathMatrixTest, IndexOperatorTest)
{
  MathMatrix<double> matrix1(4, 4);
  for (int row = 0, numRows = matrix1.rows(); row < numRows; ++row)
  {
    for (int column = 0, numCols = matrix1.cols(); column < numCols; ++column)
    {
      matrix1(row, column) = row + column;
    }
  }

  for (int row = 0, numRows = matrix1.rows(); row < numRows; ++row)
  {
    for (int column = 0, numCols = matrix1.cols(); column < numCols; ++column)
    {
      EXPECT_EQ(row + column, matrix1(row, column));
    }
  }

  EXPECT_THROW(matrix1(5, 2), std::out_of_range);
  EXPECT_THROW(matrix1(2, 5), std::out_of_range);
}

TEST_F(MathMatrixTest, CopyConstructor_EquilvalenceOperator)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  MathMatrix<double> matrixCopy(matrix1);

  EXPECT_TRUE(matrixCopy == matrix1);

  matrix1(0, 0) = 3;
  EXPECT_TRUE(matrixCopy != matrix1);
}

TEST_F(MathMatrixTest, AssignmentOperator)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  MathMatrix<double> matrix2;
  matrix2 = matrix1;

  EXPECT_TRUE(matrix1 == matrix2);

  matrix2(1, 0) = 7;
  EXPECT_TRUE(matrix1 != matrix2);
}

TEST_F(MathMatrixTest, Add_Sub)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  MathMatrix<double> matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  
  MathMatrix<double> matrix3(matrix2);

  MathMatrix<double> matrix4(2, 2);
  matrix4(0, 0) = 3;
  matrix4(0, 1) = 5;
  matrix4(1, 0) = 7;
  matrix4(1, 1) = 9;

  MathMatrix<double> matrix5 = matrix3 + matrix1;
  matrix3 += matrix1;

  EXPECT_TRUE(matrix5 == matrix3);
  EXPECT_TRUE(matrix3 == matrix4);

  MathMatrix<double> matrix6 = matrix4 - matrix2;
  matrix4 -= matrix2;
  EXPECT_TRUE(matrix4 == matrix1);
  EXPECT_TRUE(matrix4 == matrix6);
}

TEST_F(MathMatrixTest, Transpose)
{
  MathMatrix<double> matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  MathMatrix<double> matrix1 = matrix2.transpose();

  EXPECT_EQ(matrix1(0, 1), matrix2(1, 0)); 

  EXPECT_TRUE(matrix1.transpose() == matrix2);
}

TEST_F(MathMatrixTest, MatrixMultiply)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 1;

  MathMatrix<double> matrix2(2, 3);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;
  matrix2(1, 2) = 2;
 
  MathMatrix<double> result(2, 3);
  result(0, 0) = 4;
  result(0, 1) = 5;
  result(0, 2) = 7;
  result(1, 0) = 7;
  result(1, 1) = 10;
  result(1, 2) = 11;

  EXPECT_TRUE(result == matrix1 * matrix2);
  EXPECT_THROW(matrix2 * matrix1, std::domain_error);
}

TEST_F(MathMatrixTest, MatrixScalerMultiply)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 1;

  MathMatrix<double> matrix2(2, 2);
  matrix2(0, 0) = 3;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 3;

  EXPECT_TRUE(matrix2 == matrix1*3);
}

TEST_F(MathMatrixTest, MatrixVectorMultiply)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 1;

  MathVector<double> vec(2);
  vec[0] = 1;
  vec[1] = 2;

  MathVector<double> result(2);
  result[0] = 5;
  result[1] = 5;

  EXPECT_TRUE(result == matrix1*vec);
}

TEST_F(MathMatrixTest, IMathMatrixTest)
{
  MathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 1;

  MathMatrix<double> matrix(2, 3);
  IMathMatrix<double>& matrix2 = matrix;
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;
  matrix2(1, 2) = 2;
 
  MathMatrix<double> result(2, 3);
  result(0, 0) = 4;
  result(0, 1) = 5;
  result(0, 2) = 7;
  result(1, 0) = 7;
  result(1, 1) = 10;
  result(1, 2) = 11;

  EXPECT_TRUE(result == matrix1 * matrix2);

  matrix1 = matrix2;
  EXPECT_TRUE(matrix1 == matrix);
}
