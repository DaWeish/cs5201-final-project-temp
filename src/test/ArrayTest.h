////////////////////////////////////////////////////////////////////////////////
// author Connor Walsh
// file   ArrayTest.h
// brief  Class to represent a set of unit tests for Array
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "gtest/gtest.h"
#include "../containers/Array.h"

class ArrayTest : public ::testing::Test {
};

TEST_F(ArrayTest, SizeConstruction)
{
  Array<double> test(20);
  EXPECT_EQ(20, test.size());
  Array<double> test2;
  EXPECT_EQ(0, test2.size());
}

TEST_F(ArrayTest, CopyConstruction)
{
  Array<double> test(5);
  test[0] = 2;
  test[1] = 4;
  test[2] = 6;
  test[3] = -2;
  test[4] = -6;

  Array<double> test2(test);
  EXPECT_EQ(test, test2);
}

TEST_F(ArrayTest, AssignmentOperator)
{
  Array<double> test(5);
  test[0] = 2;
  test[1] = 4;
  test[2] = 6;
  test[3] = -2;
  test[4] = -6;

  Array<double> test2(5);
  test2 = test;
  EXPECT_EQ(test, test2);
  test[2] = 2;
  EXPECT_NE(test, test2);
}

TEST_F(ArrayTest, Initialization)
{
  Array<int> test(10);
  for (int value : test)
  {
    EXPECT_EQ(0, value);
  }
}

TEST_F(ArrayTest, InvalidIndex)
{
  Array<int> test(10);
  EXPECT_EQ(0, test.at(4));
  EXPECT_THROW(test.at(20), std::out_of_range);
}
