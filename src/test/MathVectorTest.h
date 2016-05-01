////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   MathVectorTest.h
// brief  Class to represent a set of unit tests for MathVector
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "../linear_algebra/MathVector.h"

class MathVectorTest : public ::testing::Test {
};

TEST_F(MathVectorTest, AdditionOperator)
{
  MathVector<int> vec1(3);
  MathVector<int> vec2(3);

  vec1[0] = 4;
  vec1[1] = 6;
  vec1[2] = -2;

  vec2[0] = -4;
  vec2[1] = -6;
  vec2[2] = 2;

  MathVector<int> test = vec1 + vec2;
  EXPECT_EQ(0, test[0]);
  EXPECT_EQ(0, test[1]);
  EXPECT_EQ(0, test[2]);
}

TEST_F(MathVectorTest, SizeConstructor)
{
  MathVector<int> test(50);
  EXPECT_EQ(50, test.size());
}

TEST_F(MathVectorTest, CopyConstruction)
{
  MathVector<int> vec1(3);

  vec1[0] = 4;
  vec1[1] = 6;
  vec1[2] = -2;

  MathVector<int> test(vec1);
  EXPECT_EQ(vec1[0], test[0]);
  EXPECT_EQ(vec1[1], test[1]);
  EXPECT_EQ(vec1[2], test[2]);
}

TEST_F(MathVectorTest, EqualityOperator)
{
  MathVector<int> vec1(50);
  MathVector<int> vec2(50);

  for (auto i = 0; i < 50; ++i)
  {
    vec1[i] = i;
    vec2[i] = i;
  }

  EXPECT_EQ(vec1, vec2);
  vec1[2] = 3;
  EXPECT_NE(vec1, vec2);
  vec2[2] = 3;
  EXPECT_EQ(vec1, vec2);
}

TEST_F(MathVectorTest, CombinedAssignment)
{
  MathVector<int> vec1(3);
  MathVector<int> vec2(3);

  vec1[0] = 4;
  vec1[1] = 6;
  vec1[2] = -2;

  vec2 += vec1;
  EXPECT_EQ(vec2, vec1);
  vec2 -= vec1;
  EXPECT_EQ(0, vec2[0]);
  EXPECT_EQ(0, vec2[1]);
  EXPECT_EQ(0, vec2[2]);
  EXPECT_EQ(3, vec2.size());
}

TEST_F(MathVectorTest, IndexOperator)
{
  MathVector<int> vec1(11);
  vec1[0] = 5;
  vec1[2] = 9;
  vec1[10] = -6;

  EXPECT_EQ(-6, vec1[10]);
  EXPECT_EQ(9, vec1[2]);
  EXPECT_EQ(5, vec1[0]);
  EXPECT_EQ(0, vec1[4]);

  const MathVector<int>& test = vec1;

  EXPECT_THROW(test[20], std::out_of_range);
  EXPECT_EQ(-6, test[10]);
}

TEST_F(MathVectorTest, DotProductTest)
{
  MathVector<int> vec1(4);
  MathVector<int> vec2(4);

  vec1[0] = 2;
  vec1[1] = 4;
  vec1[2] = -2;
  vec1[3] = -4;

  vec2[0] = 2;
  vec2[1] = 4;
  vec2[2] = 2;
  vec2[3] = 4;

  EXPECT_EQ(0, vec1.dotProduct(vec2));

  vec1.zero();
  vec2.zero();

  MathVector<int> vec3(7);
  EXPECT_THROW(vec2*vec3, std::length_error);
}

TEST_F(MathVectorTest, ScalerMultiplication)
{
  MathVector<int> vec1(3);
  MathVector<int> vec2(3);
  vec1[0] = 1;
  vec1[1] = 2;
  vec1[2] = 3;
  vec1 *= 2;
  vec2[0] = 2;
  vec2[1] = 4;
  vec2[2] = 6;
  EXPECT_EQ(vec1, vec2);
}

TEST_F(MathVectorTest, Magnitude)
{
  MathVector<double> test(5);
  test[0] = 3.0;
  test[1] = 2.0;
  test[2] = 1.0;
  test[3] = 1.0;
  test[4] = 1.0;
  EXPECT_EQ(4.0, test.getMagnitude());
}
