// This is a basic google test
//

#include <stdexcept>

#include "gtest/gtest.h"
#include "../containers/ArrayList.h"

class ArrayListTest : public ::testing::Test {
  protected:
    virtual void SetUp() {}

    ArrayList<int> intList0;
    ArrayList<int> intList1;
};

TEST_F(ArrayListTest, DefaultConstruction)
{
  EXPECT_TRUE(intList1.empty());
  EXPECT_EQ(0, intList1.size());
  EXPECT_EQ(0, intList1.capacity());
}

TEST_F(ArrayListTest, Push_Back)
{
  intList0.push_back(0);
  intList0.push_back(1);

  EXPECT_EQ(2, intList0.size());

  for (auto i = 0; i < 100; ++i)
  {
    intList1.push_back(i);
  }
  EXPECT_EQ(100, intList1.size());
}

TEST_F(ArrayListTest, EqualityOperator)
{
  for (auto i = 0; i < 10; ++i)
  {
    intList0.push_back(i);
    intList1.push_back(i);
  }

  EXPECT_TRUE(intList0 == intList1);

  intList0.push_back(34);
  EXPECT_TRUE(intList0 != intList1);

  intList1.push_back(34);
  EXPECT_TRUE(intList0 == intList1);
}

TEST_F(ArrayListTest, CopyConstruction)
{
  for (auto i = 0; i < 100; ++i)
  {
    intList1.push_back(i);
  }

  ArrayList<int> testCopy(intList1);

  EXPECT_EQ(testCopy.size(), intList1.size());
  EXPECT_LE(testCopy.capacity(), intList1.capacity());
  EXPECT_TRUE(testCopy == intList1);
}

TEST_F(ArrayListTest, Resizing)
{
  for (auto i = 0; i < 100; ++i)
  {
    intList1.push_back(i);
  }

  intList1.resize(50);
  EXPECT_EQ(50, intList1.size());

  intList1.resize(200);
  EXPECT_EQ(200, intList1.size());
}

TEST_F(ArrayListTest, Swapping)
{
  intList0.push_back(0);
  intList0.push_back(2);
  intList0.push_back(4);

  ArrayList<int> test0(intList0);
  EXPECT_TRUE(intList0 == test0);

  intList1.push_back(1);
  intList1.push_back(3);
  intList1.push_back(5);

  ArrayList<int> test1(intList1);
  EXPECT_TRUE(intList1 == test1);

  test0.swap(test1);

  EXPECT_TRUE(intList0 == test1);
  EXPECT_TRUE(intList1 == test0);
}

TEST_F(ArrayListTest, Clearing)
{
  for (auto i = 0; i < 100; ++i)
  {
    intList1.push_back(i);
  }

  EXPECT_EQ(100, intList1.size());
  intList1.clear();

  EXPECT_EQ(0, intList1.size());
}

TEST_F(ArrayListTest, AssignmentOperator)
{
  intList0.push_back(2);
  intList0.push_back(4);
  intList0.push_back(8);
  intList0.push_back(16);

  intList1 = intList0;
  EXPECT_EQ(intList0, intList1);
}

TEST_F(ArrayListTest, MoveConstruction)
{
  ArrayList<int> test(ArrayList<int>(20));
  EXPECT_EQ(20, test.size());
}

TEST_F(ArrayListTest, IndexOperator)
{
  intList0.push_back(20);
  intList0.push_back(4);
  
  EXPECT_EQ(20, intList0[0]);
  EXPECT_EQ(4, intList0[1]);

  intList0[0] = 42;
  EXPECT_EQ(42, intList0[0]);
}

TEST_F(ArrayListTest, AtFunction)
{
  for (auto i = 0; i < 10; ++i)
  {
    intList0.push_back(i*2);
  }

  EXPECT_EQ(4, intList0.at(2));
  EXPECT_THROW(intList0.at(20), std::out_of_range);
}
