/************************************************************
	Filename: test_SymmetricalMatrix.cpp
	Programmer: Paul Sites
	Class: CS5201
	Assignment:	6 - An Abstract Matrix Class w/ More Derivatives
  Date: 2015.04.22
	Desc:
		This is the SymmetricalMatrix unit-test file. It contains methods to test the SymmetricalMatrix class.
************************************************************/
#if google_test_enabled

#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

#include "SymmetricalMatrix.h"

using std::cout;
using std::endl;
using std::log;

TEST(SymmetricalMatrixTest, Print)
{
  /* This one is just a visual test to make sure 
   * that the matrix is printing out as expected.
   */
   
  SymmetricalMatrix<int> sym(4);
  int z = 0;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      sym(i, j) = z++;
  //cout<<sym<<endl;
  
  ASSERT_EQ(true,true);
}

TEST(SymmetricalMatrixTest, Operator_Assignment)
{
  SymmetricalMatrix<int> orignal(4);
  SymmetricalMatrix<int> copy;
  int z = 0;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      orignal(i, j) = z++;
      
  copy = orignal;

  ASSERT_EQ(orignal,copy);
}

TEST(SymmetricalMatrixTest, Operator_MatrixAssignment)
{
  SymmetricalMatrix<int> expected(4);
  SymmetricalMatrix<int> copy;
  int z = 0;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++){
      expected(i, j) = z++;
    }
  
  Matrix<int> original(expected);

  copy = original;

  ASSERT_EQ(expected,copy);
}

TEST(SymmetricalMatrixTest, Symmetric_Verify)
{
  SymmetricalMatrix<int> sym(5);
  int z = 0;
  for(int i=0; i<5; i++)
    for(int j=0; j<5; j++){
      sym(i, j) = z++;
    }
  
  for(int i=0; i<5; i++)
    for(int j=0; j<5; j++){
      ASSERT_EQ(sym(i, j),sym(j, i));
    }
}

TEST(SymmetricalMatrixTest, Operator_Add)
{
  SymmetricalMatrix<int> sym1(4);
  SymmetricalMatrix<int> sym2(4);

  sym1.SetAll(10);
  sym2.SetAll(15);

  SymmetricalMatrix<int> result(sym1 + sym2);
  
  SymmetricalMatrix<int> expected(4);
  expected.SetAll(25);

  ASSERT_EQ(result,expected);
}

TEST(SymmetricalMatrixTest, Operator_AddEquals)
{
  SymmetricalMatrix<int> sym1(4);
  SymmetricalMatrix<int> sym2(4);

  sym1.SetAll(10);
  sym2.SetAll(15);
  sym1 += sym2;

  SymmetricalMatrix<int> expected(4);
  expected.SetAll(25);

  ASSERT_EQ(sym1,expected);
}

TEST(SymmetricalMatrixTest, Operator_Sub)
{
  SymmetricalMatrix<int> sym1(4);
  SymmetricalMatrix<int> sym2(4);

  sym1.SetAll(10);
  sym2.SetAll(15);

  SymmetricalMatrix<int> result(sym1-sym2);

  SymmetricalMatrix<int> expected(4);
  expected.SetAll(-5);

  ASSERT_EQ(result,expected);
}

TEST(SymmetricalMatrixTest, Operator_SubEquals)
{
  SymmetricalMatrix<int> sym1(4);
  SymmetricalMatrix<int> sym2(4);

  sym1.SetAll(10);
  sym2.SetAll(15);
  sym1 -= sym2;

  SymmetricalMatrix<int> expected(4);
  expected.SetAll(-5);

  ASSERT_EQ(sym1,expected);
}

TEST(SymmetricalMatrixTest, Operator_VectorMult)
{
  SymmetricalMatrix<int> A(3);
  A.SetAll(4);
  
  Vector<int> x(3);
  x[0] = 2;
  x[1] = 2;
  x[2] = 2;
  
  Vector<int> b = A*x;

  Vector<int> expect(3);
  expect[0] = 24;
  expect[1] = 24;
  expect[2] = 24;
  
  ASSERT_EQ(expect, b);
}

#endif
