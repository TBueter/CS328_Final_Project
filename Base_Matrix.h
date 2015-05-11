////////////////////////////////////////////////////////////////
///  Base_Matrix.h
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
///
///  Programmer :  Travis Bueter & Paul Sites
///  Assignment :  Final Project - Solving Poisson's Equation
///
///  Instructor :  Prof. Clayton Price
///  Grader     :  Dr. Nathan "Waffles" Eloe, a.k.a. C++ Guru
///                Ph.D., Computer Science
///                B.S., Computer Science
///                B.S., Physics
///                Judan, C++ Ninjutsu
/// 
///  Course     :  CS5201
///  Semester   :  Spring 2015
///
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
///  Templated abstract class definition for mathematical matrix
///  representations.
////////////////////////////////////////////////////////////////

#ifndef  BASE_MATRIX_H
#define  BASE_MATRIX_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <initializer_list>
#include "Vector.h"
#include "OutOfRangeErr.h"
#include "IncompatibleVectorErr.h"
#include "IncompatibleMatrixErr.h"
using namespace std;


template<class T>
class Matrix;

//Used for identifying matrix types when using a reference to the
//abstract class type.
enum MatrixType
{
    STANDARD = 0,
    UPPERTRIANGULAR,
    LOWERTRIANGULAR,
    SYMMETRICAL,
    DIAGONAL,
    TRIDIAGONAL,
    MESH
};

////////////////////////////////////////////////////////////////
///  Class: Base_Matrix  
///  NOTE:  In the function documentation, you will often see
///         '*this' and 'component values' terms. *this is the 
///         term used to refer to the calling object. Component
///         values is the term used to refer to the segments of
///         allocated memory ptr_to_data points to. I don't feel
///         these were the best usage of words but didn't know
///         how to refer to them properly in the documentation.   
////////////////////////////////////////////////////////////////
template <class T>
class Base_Matrix
{
    public:
        virtual ~Base_Matrix(){};
        
        virtual T operator()(const unsigned int row, const unsigned int col) const = 0;

        virtual T& operator()(const unsigned int row, const unsigned int col) = 0;
        
        virtual Matrix<T> operator*(const Base_Matrix<T>& rhs) const = 0;
        
        virtual Matrix<T> operator+(const Base_Matrix<T>& rhs) const = 0;
        
        virtual Matrix<T> operator-(const Base_Matrix<T>& rhs) const = 0;

        virtual unsigned int getSize() const = 0;

        virtual unsigned int numRows() const = 0;

        virtual unsigned int numCols() const = 0;
        
        virtual void Resize(const unsigned int rows, const unsigned int cols) = 0;
        
        virtual MatrixType getType() const = 0;

        virtual T* getPtr() const = 0;

};
#endif //BASE_MATRIX_H
