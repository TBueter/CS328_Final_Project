/* file test_Vector.cpp
 * author Nathan Eloe (nwe5g8@mst.edu): modified by Travis Bueter & Paul Sites
 * brief The unit tests for the Vector class
 */
#if google_test_enabled
 
#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

#include "Vector.h"

using std::cout;
using std::endl;
using std::log;

TEST(VectorTest, CorrectDefaultSize)
{
  Vector<int> a;
  ASSERT_EQ(0,a.getSize());
}

TEST(VectorTest, CorrectDefaultMaxSize)
{
  Vector<int> a;
  ASSERT_EQ(0,a.getSize());
}

TEST(VectorTest, ConstructorSetSize)
{
  Vector<int> a(100);
  ASSERT_EQ(100,a.getSize());
}

TEST(VectorTest, BracketReadNegativeIndex)
{
  Vector<int> a;
  ASSERT_THROW(int test = a[-1], Out_Of_Range_Err);
}

TEST(VectorTest, BracketReadIndexLargerThanSize)
{
  Vector<int> a;
  ASSERT_THROW(int test = a[3], Out_Of_Range_Err);
}

TEST(VectorTest, BracketReadIndexIsSize)
{
  Vector<int> a;
  ASSERT_THROW(int test = a[0], Out_Of_Range_Err);
}

TEST(VectorTest, BracketWriteNegativeIndex)
{
  Vector<int> a;
  ASSERT_THROW(a[-1]=1, Out_Of_Range_Err);
}

TEST(VectorTest, BracketWriteIndexLargerThanSize)
{
  Vector<int> a;
  ASSERT_THROW(a[3]=1, Out_Of_Range_Err);
}

TEST(VectorTest, BracketWriteIndexIsSize)
{
  Vector<int> a;
  ASSERT_THROW(a[0]=1, Out_Of_Range_Err);
}

TEST(VectorTest, BracketWriteValue)
{
  Vector<double> a(1);
  a[0] = 1;
  ASSERT_EQ(a[0] == 1, true);
}

TEST(VectorTest, AssignmentEmpty)
{
    Vector<int> a,b;
    a=b;
    ASSERT_EQ(0,a.getSize());
    ASSERT_EQ(0,b.getSize());
}

TEST(VectorTest, AssignmentPopulated)
{
    Vector<int> a(100),b(100);
    for (int i=0; i<100; i++)
        a[i];
    b=a;
    ASSERT_EQ(a.getSize(),b.getSize());
    ASSERT_EQ(a.getSize(), b.getSize());
    for (int i=0; i<100; i++)
        ASSERT_EQ(a[i],b[i]);
}

TEST(VectorTest, AssignmentScalar)
{
    Vector<int> a(100);
    a = 100;
    for (int i=0; i<100; i++)
        ASSERT_EQ(a[i],100);
}

TEST(VectorTest, CompareEqual)
{
  const int SIZE = 1000;
  Vector<int> a(SIZE);
  Vector<int> b(SIZE);
  for (int i=0; i<SIZE; i++)
  {
    a[i] = i;
    b[i] = i;
  }
  ASSERT_EQ(a == b, true);
  a[999] = 9;
  ASSERT_EQ(a == b, false);
}

TEST(VectorTest, CompareNotEqual)
{
  const int SIZE = 1000;
  Vector<int> a(SIZE);
  Vector<int> b(SIZE);
  for (int i=0; i<SIZE; i++)
  {
    a[i] = i;
    b[i] = i+1;
  }
  ASSERT_EQ(a != b, true);
}

TEST(VectorTest, Addition)
{
  const int SIZE = 1000;
  Vector<int> a(SIZE);
  Vector<int> b(SIZE);
  Vector<int> expect(SIZE);
  Vector<int> result;
  for (int i=0; i<1000; i++)
  {
    a[i] = i;
    b[i] = i;
    expect[i] = i*2;
  }
  result = a + b;   
  ASSERT_EQ(result == expect, true);
}

TEST(VectorTest, Subtraction)
{
  const int SIZE = 1000;
  Vector<int> a(SIZE);
  Vector<int> b(SIZE);
  Vector<int> expect(SIZE);
  Vector<int> result;
  for (int i=0; i<1000; i++)
  {
    a[i] = i*6;
    b[i] = i*2;
    expect[i] = i*4;
  }
  result = a - b;   
  ASSERT_EQ(result == expect, true);
}

TEST(VectorTest, DotProduct)
{
  Vector<int> a(3);
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  
  Vector<int> b(3);
  b[0] = 4;
  b[1] = -5;
  b[2] = 6;
  
  ASSERT_EQ(a*b, 12);
}

#endif