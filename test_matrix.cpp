/************************************************************
	Filename: test_matrix.cpp
	Programmer: Paul Sites
	Class: CS5201
	Assignment:	4 - A Parameterized Matrix Class and Gaussian Elimination
  Date: 2015.03.16
	Desc:
		This is the Matrix unit-test file. It contains methods to test the Matrix class.
************************************************************/
#if google_test_enabled

#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

#include "Matrix.h"

using std::cout;
using std::endl;
using std::log;

TEST(MatrixTest, CorrectDefaultSize)
{
  Matrix<int> a;
  ASSERT_EQ(0,a.numRows());
  ASSERT_EQ(0,a.numCols());
}

TEST(MatrixTest, CopyConstructor)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<a.numRows(); i++)
    for(int j=0; j<a.numCols(); j++)
      a(i, j) = 50;
      
  Matrix<int> b(a);
  for(int i=0; i<b.numRows(); i++)
    for(int j=0; j<b.numCols(); j++)
      ASSERT_EQ( b(i, j), 50);
}

TEST(MatrixTest, Set_Values)
{
  Matrix<int> a(10, 10);
  
  for(int i=0; i<10; i++)
    for(int j=0; j<10; j++)
      a(i, j) = 5;
  
  //ASSERT_EQ(a(i,j),5);
  // ASSERT_EQ(10,a.numCols());
}

TEST(MatrixTest, ConstructorSetSize_Indep)
{
  Matrix<int> a(100, 50);
  ASSERT_EQ(100,a.numRows());
  ASSERT_EQ(50,a.numCols());
}

TEST(MatrixTest, FillMatrix)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      a(i, j) = 50;
  
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( a(i, j), 50);
}

TEST(MatrixTest, SetAll)
{
  Matrix<int> a(4, 4);
  a.SetAll(50);
  
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( a(i, j), 50);
}

TEST(MatrixTest, FillMatrix_2)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      a(i, j) = (i+1)*(j+1);
  
  //cout<<a<<endl;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( a(i, j), (i+1)*(j+1));
}

TEST(MatrixTest, Operator_Plus)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      a(i, j) = (i+1)*(j+1);
      
  Matrix<int> b(a);
  
  Matrix<int> c = a + b;
  
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( c(i, j), ((i+1)*(j+1))*2);
}

TEST(MatrixTest, Operator_PlusEquals)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      a(i, j) = (i+1)*(j+1);
      
  Matrix<int> b(a);  
  b += a;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( b(i, j), ((i+1)*(j+1))*2);
}

TEST(MatrixTest, Operator_Plus_Exception)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      a(i, j) = (i+1)*(j+1);
      
  Matrix<int> b(3, 2);
  for(int i=0; i<3; i++)
    for(int j=0; j<2; j++)
      b(i, j) = (i+1)*(j+1);
  
  ASSERT_THROW(a + b, Incompatible_Matrix_Err);
}

TEST(MatrixTest, Operator_Minus)
{
  Matrix<int> a(4, 4);
  Matrix<int> b(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
    {
      a(i, j) = ((i+1)*(j+1))*2;
      b(i, j) = (i+1)*(j+1);
    } 
    
  Matrix<int> c = a - b;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( c(i, j), ((i+1)*(j+1)));
}

TEST(MatrixTest, Operator_Minus_Exception)
{
  Matrix<int> a(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      a(i, j) = (i+1)*(j+1);
      
  Matrix<int> b(3, 2);
  for(int i=0; i<3; i++)
    for(int j=0; j<2; j++)
      b(i, j) = (i+1)*(j+1);
  
  ASSERT_THROW(a - b, Incompatible_Matrix_Err);
}

TEST(MatrixTest, Operator_MinusEquals)
{
  Matrix<int> a(4, 4);
  Matrix<int> b(4, 4);
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
    {
      a(i, j) = ((i+1)*(j+1))*2;
      b(i, j) = (i+1)*(j+1);
    } 
    
  a -= b;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      ASSERT_EQ( b(i, j), ((i+1)*(j+1)));
}


TEST(MatrixTest, Operator_Mult)
{
  Matrix<int> a(3, 2);
  Matrix<int> b(2, 3);
  Matrix<int> c(3, 3);
  
  int val = 1;
  for(int j=0; j<a.numCols(); j++)
    for(int i=0; i<a.numRows(); i++)
      a(i, j) = val++;
  for(int i=0; i<b.numRows(); i++)
    for(int j=0; j<b.numCols(); j++)
      b(i, j) = val++;
  
  Matrix<int> ans(3, 3);
  ans(0, 0) = 47; ans(0, 1) = 52; ans(0, 2) = 57;
  ans(1, 0) = 64; ans(1, 1) = 71; ans(1, 2) = 78;
  ans(2, 0) = 81; ans(2, 1) = 90; ans(2, 2) = 99;
  c = a * b;
  
  ASSERT_EQ(ans, c);
}


TEST(MatrixTest, MatrixTranspose)
{
  Matrix<int> orig(2, 3);
  int val = 1;
  for(int i=0; i<orig.numRows(); i++)
    for(int j=0; j<orig.numCols(); j++)
      orig(i, j) = val++;
  
  Matrix<int> expect(3, 2);
  val = 1;
  for(int j=0; j<expect.numCols(); j++)
    for(int i=0; i<expect.numRows(); i++)
      expect(i, j) = val++;
  
  Matrix<int> transMat = orig.Transpose();
  
  ASSERT_EQ(transMat, expect);
}

TEST(MatrixTest, MatrixVectorMult)
{
  Matrix<int> A(2, 3);
  A(0, 0) = 1; A(0, 1) = -1; A(0, 2) = 2;
  A(1, 0) = 0; A(1, 1) = -3; A(1, 2) = 1;
  
  Vector<int> x(3);
  x[0] = 2;
  x[1] = 1;
  x[2] = 0;
  
  Vector<int> b = A*x;
    
  Vector<int> expect(2);
  expect[0] = 1;
  expect[1] = -3;
  
  ASSERT_EQ(b, expect);
}
#endif