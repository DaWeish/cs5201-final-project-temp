////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   UpTriangleMathVectorTest.h
// brief  Class to represent a set of unit tests for UpTriangleMathMatrix's
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"
#include "../linear_algebra/math_matrix/UpTriangleMathMatrix.h"

class UpTriangleMathMatrixTest : public ::testing::Test {};

TEST_F(UpTriangleMathMatrixTest, DefaultConstruction)
{
  UpTriangleMathMatrix<double> matrix1;

  EXPECT_EQ(0, matrix1.rows());
  EXPECT_EQ(0, matrix1.cols());
}

TEST_F(UpTriangleMathMatrixTest, SizeConstruction)
{
  UpTriangleMathMatrix<double> matrix1(4, 4);
  EXPECT_EQ(4, matrix1.rows());
  EXPECT_EQ(4, matrix1.cols());

  UpTriangleMathMatrix<double> matrix2(5, 7);
  EXPECT_EQ(5, matrix2.rows());
  EXPECT_EQ(7, matrix2.cols());
}

TEST_F(UpTriangleMathMatrixTest, IndexOperatorTest)
{
  UpTriangleMathMatrix<double> matrix1(4, 4);
  for (int row = 0, numRows = matrix1.rows(); row < numRows; ++row)
  {
    for (int column = row, numCols = matrix1.cols(); column < numCols; ++column)
    {
      matrix1(row, column) = row + column;
    }
  }

  for (int row = 0, numRows = matrix1.rows(); row < numRows; ++row)
  {
    for (int column = row, numCols = matrix1.cols(); column < numCols; ++column)
    {
      EXPECT_EQ(row + column, matrix1(row, column));
    }
  }

  EXPECT_THROW(matrix1(5, 2), std::out_of_range);
  EXPECT_THROW(matrix1(2, 5), std::out_of_range);
}

TEST_F(UpTriangleMathMatrixTest, CopyConstructor_EquilvalenceOperator)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 1) = 4;

  UpTriangleMathMatrix<double> matrixCopy(matrix1);

  EXPECT_TRUE(matrixCopy == matrix1);

  matrix1(0, 0) = 3;
  EXPECT_TRUE(matrixCopy != matrix1);
}

TEST_F(UpTriangleMathMatrixTest, AssignmentOperator)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 1) = 4;

  MathMatrix<double> matrix2;
  matrix2 = matrix1;
  IMathMatrix<double>& matrix2ref = matrix2;

  EXPECT_TRUE(matrix1 == matrix2ref);

  matrix2(1, 0) = 7;

  EXPECT_TRUE(matrix1 != matrix2);
}

TEST_F(UpTriangleMathMatrixTest, Add_Sub)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 1) = 4;

  UpTriangleMathMatrix<double> matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 1) = 5;
  
  UpTriangleMathMatrix<double> matrix3(matrix2);

  UpTriangleMathMatrix<double> matrix4(2, 2);
  matrix4(0, 0) = 3;
  matrix4(0, 1) = 5;
  matrix4(1, 1) = 9;

  UpTriangleMathMatrix<double> matrix5 = matrix3 + matrix1;
  matrix3 += matrix1;

  EXPECT_TRUE(matrix5 == matrix3);
  EXPECT_TRUE(matrix3 == matrix4);

  MathMatrix<double> matrix6 = (matrix4 - matrix2);
  matrix4 -= matrix2;

  EXPECT_TRUE(matrix4 == matrix1);
  EXPECT_TRUE(matrix4 == matrix6);
}

TEST_F(UpTriangleMathMatrixTest, Transpose)
{
  UpTriangleMathMatrix<double> matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 1) = 5;

  LowTriangleMathMatrix<double> matrix1 = matrix2.transpose();

  EXPECT_EQ(matrix2(0, 1), matrix1(1, 0)); 

  EXPECT_TRUE(matrix1.transpose() == matrix2);
}

TEST_F(UpTriangleMathMatrixTest, MatrixMultiply)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
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
  result(1, 0) = 1;
  result(1, 1) = 1;
  result(1, 2) = 2;

  EXPECT_TRUE(result == matrix1 * matrix2);
  EXPECT_THROW(matrix2 * matrix1, std::domain_error);
}

TEST_F(UpTriangleMathMatrixTest, MatrixScalerMultiply)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 1) = 1;

  MathMatrix<double> matrix2(2, 2);
  matrix2(0, 0) = 3;
  matrix2(0, 1) = 6;
  matrix2(1, 1) = 3;

  EXPECT_TRUE(matrix2 == matrix1*3);
}

TEST_F(UpTriangleMathMatrixTest, MatrixVectorMultiply)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 1) = 1;

  MathVector<double> vec(2);
  vec[0] = 1;
  vec[1] = 2;

  MathVector<double> result(2);
  result[0] = 5;
  result[1] = 2;

  EXPECT_TRUE(result == matrix1*vec);
}

TEST_F(UpTriangleMathMatrixTest, IMathMatrixTest)
{
  UpTriangleMathMatrix<double> matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 1) = 1;

  UpTriangleMathMatrix<double> matrix(2, 3);
  IMathMatrix<double>& matrix2 = matrix;
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(0, 2) = 3;
  matrix2(1, 1) = 1;
  matrix2(1, 2) = 2;
 
  MathMatrix<double> result(2, 3);
  result(0, 0) = 2;
  result(0, 1) = 5;
  result(0, 2) = 7;
  result(1, 0) = 0;
  result(1, 1) = 1;
  result(1, 2) = 2;

  EXPECT_TRUE(result == matrix1 * matrix2);

  matrix1 = matrix2;
  EXPECT_TRUE(matrix1 == matrix);
}
