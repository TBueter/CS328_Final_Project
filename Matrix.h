////////////////////////////////////////////////////////////////
///  Matrix.h
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
///  Templated class definition for a mathematical dense matrix
///  representation. This class is based on the array class
///  described in the Scientific and Engineering C++ book for 
///  this course.
////////////////////////////////////////////////////////////////

#ifndef  MATRIX_H
#define  MATRIX_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <initializer_list>
#include "Base_Matrix.h"
#include "Vector.h"
#include "OutOfRangeErr.h"
#include "IncompatibleVectorErr.h"
#include "IncompatibleMatrixErr.h"
using namespace std;

////////////////////////////////////////////////////////////////
///  Class: Matrix  
///  NOTE: In the function documentation, you will often see
///        '*this' and 'component values' terms. *this is the 
///        term used to refer to the calling object. Component
///        values is the term used to refer to the segments of
///        allocated memory ptr_to_data points to. I don't feel
///        these were the best usage of words but didn't know
///        how to refer to them properly in the documentation.   
////////////////////////////////////////////////////////////////
template <class T>
class Matrix : public Base_Matrix<T>
{
    public:
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix (Default)
        ///  Brief:  Default constructor for class. Creates an empty 
        ///          Matrix.
        ///  Pre:    None
        ///  Post:   An empty Matrix is defined with size equal to zero
        ///          and no memory allocated.
        ////////////////////////////////////////////////////////////////
        Matrix();
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix
        ///  Brief:  Primary constructor for class. Creates a m-by-n 
        ///          Matrix with components.
        ///  Pre:    None
        ///  Post:   A Matrix is defined with 'm' rows and 'n' columns.
        ///          Memory is allocated for storing m*n components, all 
        ///          initialized to zero. 
        ///  Param:  rows - Non-negative integer used to define the  
        ///          number of rows for the matrix.
        ///  Param:  cols - Non-negative integer used to define the  
        ///          number of columns for the matrix.
        ////////////////////////////////////////////////////////////////
        Matrix(unsigned int rows, unsigned int columns);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix
        ///  Brief:  Alternate constructor for class. Creates a Vector
        ///          with n components.
        ///  Pre:    None
        ///  Post:   A Matrix is defined with 'm' rows and 'n' columns.
        ///          Memory is allocated for storing m*n components, all 
        ///          initialized to the given value. 
        ///  Param:  rows - Non-negative integer used to define the  
        ///          number of rows for the matrix.
        ///  Param:  cols - Non-negative integer used to define the  
        ///          number of columns for the matrix.
        ///  Param:  value - Instance of template type that all 
        ///          elements of the matrix are set to.
        ////////////////////////////////////////////////////////////////
        Matrix(unsigned int rows, unsigned int cols, T value);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix (Copy)
        ///  Brief:  Copy constructor for class. Creates a new Matrix 
        ///          that is a clone of the given Matrix.
        ///  Pre:    None
        ///  Post:   A Matrix is defined with the same number of rows
        ///          and columns as the source Matrix and with copies
        ///          of the same components. 
        ///  Param:  src - Another instance of a Matrix to be copied.
        ////////////////////////////////////////////////////////////////
        Matrix(const Matrix<T>& src);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix (Copy)
        ///  Brief:  Copy constructor for class. Creates a new Matrix 
        ///          that is a clone of the given Matrix.
        ///  Pre:    None
        ///  Post:   A Matrix is defined with the same number of rows
        ///          and columns as the source Matrix and with copies
        ///          of the same components. 
        ///  Param:  src - A Base_Matrix to be copied.
        ////////////////////////////////////////////////////////////////
        Matrix<T>(const Base_Matrix<T>& src);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix
        ///  Brief:  Initialization constructor for class. Creates a
        ///          Matrix with dimensions based on the sizes of the
        ///          initializer lists. Follows this format:
        ///                 { {...}, {...}, ... {...} }
        ///          Number of rows 'm' is equal to the number of
        ///          internal brackets. Number of columns 'n' is equal
        ///          to the number of elements of the internal brackets.
        ///  Pre:    The internal brackets, {...}, *should* have the 
        ///          same number of elements. An error will be thrown
        ///          if any differ from the size of the first set.
        ///  Post:   The internal brackets, {...}, should have the 
        ///          same number of elements. An error will be thrown
        ///          if any differ from the size of the first set.
        ///          A Matrix is defined with 'm' rows and 'n' columns.
        ///          Memory is allocated for storing m*n components, all 
        ///          initialized to the given values. 
        ///  Param:  lists - Initializer list of initializer lists of 
        ///          instances of a templated type. These values are 
        ///          used to populate the Matrix.
        ////////////////////////////////////////////////////////////////
        Matrix(initializer_list< initializer_list<T> > list);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~Matrix (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   Any allocated memory for the class is deallocated.
        ////////////////////////////////////////////////////////////////
        ~Matrix();
        
        
        ///////////////////// Virtual Functions ////////////////////////

        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Accessor)
        ///  Brief:  Overloaded accessor operator for class. Allows 
        ///          read access to the components of the Matrix. 
        ///  Pre:    row < m_rows
        ///  Pre:    col < m_cols
        ///  Post:   None
        ///  Param:  row - Non-negative index value for a Matrix 
        ///          row location.
        ///  Param:  col - Non-negative index value for a Matrix 
        ///          column location.
        ///  Return: Returns the value stored at the offset memory 
        ///          location from ptr_to_data. Offset is:
        ///             m_cols*row+col
        ////////////////////////////////////////////////////////////////
        virtual T operator()(const unsigned int row, const unsigned int col) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Mutator)
        ///  Brief:  Overloaded mutator operator for class. Allows 
        ///          write access to the components of the Matrix. 
        ///  Pre:    row < m_rows
        ///          col < m_cols
        ///  Post:   None
        ///  Param:  row - Non-negative index value for a Matrix 
        ///          row location.
        ///  Param:  col - Non-negative index value for a Matrix 
        ///          column location.
        ///  Return: Returns the address of the offset memory 
        ///          location from ptr_to_data. Offset is:
        ///             m_cols*row+col
        ////////////////////////////////////////////////////////////////
        virtual T& operator()(const unsigned int row, const unsigned int col);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Matrix Multiplication)
        ///  Brief:  Overloaded multiplication operator for class.
        ///          Performs multiplication on two Matrix instances.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T += T (addition) must be defined.
        ///          T * T (multiplication) must be defined with result
        ///          T.
        ///          T = 0 must be a valid assignment.
        ///  Post:   If Matrices are unequal sizes, an incompatibility 
        ///          error is thrown.
        ///          Otherwise, a new Matrix instance is created and is 
        ///          the product of *this and rhs.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns the new Matrix instance.
        ////////////////////////////////////////////////////////////////
        virtual Matrix<T> operator*(const Base_Matrix<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   + (Addition)
        ///  Brief:  Overloaded addition operator for class. 
        ///  Pre:    T = T (assignment) must be defined.
        ///          T + T (addition) must be defined with result T.
        ///  Post:   If Matrices are unequal sizes, an incompatibility 
        ///          error is thrown.
        ///          Otherwise, a new Matrix instance of the same size
        ///          is created and component values are the sum of those
        ///          at the same indexes of *this and rhs.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns the new Matrix instance.
        ////////////////////////////////////////////////////////////////
        virtual Matrix<T> operator+(const Base_Matrix<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   - (Subtraction)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///  Pre:    T = T (assignment) must be defined.
        ///          T - T (subtraction) must be defined with result T.
        ///  Post:   If Matrices are unequal sizes, an incompatibility 
        ///          error is thrown.
        ///          Otherwise, a new Matrix instance of the same size
        ///          is created and component values are the sum of those
        ///          at the same indexes of *this and rhs.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns the new Matrix instance.
        ////////////////////////////////////////////////////////////////
        virtual Matrix<T> operator-(const Base_Matrix<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   getSize
        ///  Brief:  Access to size of the matrix. 
        ///  Pre:    None.
        ///  Post:   None.
        ///  Return: Returns the size of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual unsigned int getSize() const {return m_size;}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   numRows
        ///  Brief:  Access to number of rows of the matrix. 
        ///  Pre:    None.
        ///  Post:   None.
        ///  Return: Returns the number of rows of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual unsigned int numRows() const {return m_rows;}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   numCols
        ///  Brief:  Access to number of columns of the matrix. 
        ///  Pre:    None.
        ///  Post:   None.
        ///  Return: Returns the number of columns of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual unsigned int numCols() const {return m_cols;}

        ////////////////////////////////////////////////////////////////
        ///  Func:   Resize
        ///  Brief:  Deletes the data in the Matrix and resizes it.
        ///  Post:   Memory has been deleted, reallocated, and all
        ///          values set to zero.
        ////////////////////////////////////////////////////////////////
        virtual void Resize(const unsigned int rows, const unsigned int cols);
              
        ////////////////////////////////////////////////////////////////
        ///  Func:   getType
        ///  Brief:  Allows systems to know the type of matrix when 
        ///          dealing with an abstract class pointer.
        ///  Pre:    None.
        ///  Post:   None.
        ///     Return: Returns the number of rows of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual MatrixType getType() const {return STANDARD;}

        ///////////////////// Member Functions /////////////////////////
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   = (Assignment)
        ///  Brief:  Overloaded assignment operator for class. Makes 
        ///          *this a copy of src.
        ///  Pre:    None
        ///  Post:   If src is not *this, memory is reallocated, 
        ///          and m_size and component values are copied from 
        ///          src to *this.
        ///  Param:  src - Instance of an abstract Base_Matrix to be 
        ///          copied.
        ///  Return: Returns reference of self.
        ////////////////////////////////////////////////////////////////
        Matrix<T>& operator=(const Base_Matrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   = (Assignment)
        ///  Brief:  Overloaded assignment operator for class. Makes 
        ///          *this a copy of src.
        ///  Pre:    None
        ///  Post:   If src is not *this, memory is reallocated, 
        ///          and m_size and component values are copied from 
        ///          src to *this.
        ///  Param:  src - Another instance of a Matrix to be copied.
        ///  Return: Returns reference of self.
        ////////////////////////////////////////////////////////////////
        Matrix<T>& operator=(const Matrix<T>& rhs);

        ////////////////////////////////////////////////////////////////
        ///  Func:   += (Addition assignment)
        ///  Brief:  Overloaded addition assignment operator for class. 
        ///  Pre:    T += T (addition assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///          Otherwise, component values of *this are summed
        ///          with those of rhs.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////
        Matrix<T>& operator+=(const Base_Matrix<T>& rhs);
          
        ////////////////////////////////////////////////////////////////
        ///  Func:   += (Addition assignment)
        ///  Brief:  Overloaded addition assignment operator for class. 
        ///  Pre:    T += T (addition assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///          Otherwise, component values of *this are summed
        ///          with those of rhs.
        ///  Param:  rhs - Instance of a Matrix.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////      
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   - (Negative)
        ///  Brief:  Overloaded subtraction operator for class. Creates
        ///          an instance of the Matrix with component values 
        ///          multiplied by -1.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T * int (multiplication) must be defined with 
        ///          result T.
        ///  Post:   None
        ///  Return: Returns the new Matrix instance.
        ////////////////////////////////////////////////////////////////
        Matrix<T>  operator-() const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   -= (Subtraction assignment)
        ///  Brief:  Overloaded subtraction assignment operator for 
        ///          class. 
        ///  Pre:    T -= T (addition assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////
        Matrix<T>& operator-=(const Base_Matrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   -= (Subtraction assignment)
        ///  Brief:  Overloaded subtraction assignment operator for 
        ///          class. 
        ///  Pre:    T -= T (addition assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///  Param:  rhs - Instance of a Matrix.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////
        Matrix<T>& operator-=(const Matrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Unary, Matrix Scaling)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///          Scales the component values of the Matrix by the
        ///          scalar.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T * T (multiplication) must be defined with result
        ///          T.
        ///  Post:   A new Matrix instance of the same size is created 
        ///          and component values are the product of scalar.
        ///  Param:  scalar - T instance for the componets of the Matrix
        ///          to be multiplied by.
        ///  Return: Returns the new Matrix instance.
        ////////////////////////////////////////////////////////////////
        Matrix<T>  operator*(const T scalar) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   *= (Urnary, Matrix scaling assignment)
        ///  Brief:  Overloaded multiplication assigment operator for  
        ///          class. Scales the component values of the Matrix by
        ///          the scalar. 
        ///  Pre:    T *= T (multiplication assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///  Param:  scalar - T instance for the componets of the Matrix
        ///          to be multiplied by.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////
        Matrix<T>& operator*=(const T scalar);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Matrix-Vector Multiplication)
        ///  Brief:  Overloaded multiplication operator for class.
        ///          Performs multiplication on a Matrix and Vector
        ///          instance.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T += T (addition) must be defined.
        ///          T * T (multiplication) must be defined with result
        ///          T.
        ///          T = 0 must be a valid assignment.
        ///  Post:   If Matrix and Vector are unequal sizes, an 
        ///          incompatibility error is thrown.
        ///          Otherwise, a new Vector instance is created and is 
        ///          the product of *this and rhs.
        ///  Param:  rhs - Instance of a Vector.
        ///  Return: Returns the new Vector instance.
        ////////////////////////////////////////////////////////////////
        Vector<T>  operator*(const Vector<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Transpose
        ///  Brief:  Takes the transpose of the Matrix. 
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   None.
        ///  Return: Returns a new Matrix instance that is a transpose 
        ///          of the Matrix.
        ////////////////////////////////////////////////////////////////
        Matrix<T> Transpose() const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Row_Swap
        ///  Brief:  Swaps the ith and jth rows of the Matrix. 
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   Throws an error if trying to access a non-existent
        ///          row.
        ///  Return: Returns if trying to swap the same row.
        ////////////////////////////////////////////////////////////////
        void Row_Swap(const unsigned int i, const unsigned int j);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   SetAll
        ///  Brief:  Sets all the elements of the Matrix to the given
        ///          value. 
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   All elements set to the given value.
        ////////////////////////////////////////////////////////////////
        void SetAll(T value);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Zero
        ///  Brief:  Sets all the elements of the Matrix to zero. 
        ///  Pre:    T = 0 (assignment) must be defined.
        ///  Post:   All elements set to zero.
        ////////////////////////////////////////////////////////////////
        void Zero();


        ///////////////////// The Friend Zone //////////////////////////
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Binary, Matrix Scaling)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///          Scales the component values of src by scalar.
        ///  Pre:    None
        ///  Post:   None
        ///  Param:  scalar - T instance for the componets of src to be
        ///          multiplied by.
        ///  Param:  src - Instance of a Matrix.
        ///  Return: Returns the new Matrix instance.
        ////////////////////////////////////////////////////////////////
        friend Matrix<T> operator*(const T scalar, const Matrix<T>& src)
        {
            return (src * scalar);
        }
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   == (Equivalence)
        ///  Brief:  Overloaded equivalence operator for class. 
        ///  Pre:    T == T (equivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Matrix.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator==(const Matrix<T>& lhs, const Base_Matrix<T>& rhs)
        {
            if(lhs.m_rows != rhs.numRows() || lhs.m_cols != rhs.numCols())
            {
                return false;
            }
            
            for(unsigned int i = 0, size = lhs.m_rows; i < size; i++)
            {
                for(unsigned j = 0; j < size; j++)
                {
                    if(lhs(i,j) != rhs(i,j))
                        return false;
                }
            }
            return true;
        }
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   != (Inequivalence)
        ///  Brief:  Overloaded inequivalence operator for class. 
        ///  Pre:    T != T (inequivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Matrix.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns true if unequal row or column sizes or
        ///          unequal elements. Returns false if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const Matrix<T>& lhs, const Base_Matrix<T>& rhs)
        {
            if(lhs.m_rows != rhs.numRows() || lhs.m_cols != rhs.numCols())
            {
                return true;
            }
            
            for(unsigned int i = 0, size = lhs.m_rows; i < size; i++)
            {
                for(unsigned j = 0; j < size; j++)
                {
                    if(lhs(i,j) != rhs(i,j))
                        return true;
                }
            }
            return false;
        }
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   == (Equivalence)
        ///  Brief:  Overloaded equivalence operator for class. 
        ///  Pre:    T == T (equivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Matrix.
        ///  Param:  rhs - Instance of a Matrix.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
        {
            if(rhs.m_rows != lhs.m_rows || rhs.m_cols != lhs.m_cols)
            {
                return false;
            }
            
            unsigned int size = lhs.m_rows*lhs.m_cols;
            T* p = lhs.ptr_to_data + size;
            T* q = rhs.ptr_to_data + size;
            while(p > lhs.ptr_to_data)
            {
                if(*--p != *--q) 
                    return false;
            }
            
            return true;
        }
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   != (Inequivalence)
        ///  Brief:  Overloaded inequivalence operator for class. 
        ///  Pre:    T != T (inequivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Matrix.
        ///  Param:  rhs - Instance of a Matrix.
        ///  Return: Returns true if unequal row or column sizes or
        ///          unequal elements. Returns false if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
        {
            if(rhs.m_rows != lhs.m_rows || rhs.m_cols != lhs.m_cols)
            {
                return true;
            }
            
            unsigned int size = lhs.m_rows*lhs.m_cols;
            T* p = lhs.ptr_to_data + size;
            T* q = rhs.ptr_to_data + size;
            while(p > lhs.ptr_to_data)
            {
                if(*--p != *--q) 
                    return true;
            }
            
            return false;
        }

        ////////////////////////////////////////////////////////////////
        ///  Func:   << (output)
        ///  Brief:  Overloaded output operator for class.
        ///  Pre:    None
        ///  Post:   Prints out the Matrix's component values in this
        ///          format: | x_11 x_12 ... x_1n |
        ///                   ...
        ///                  | x_n1 x_n2 ... x_nn |
        ///  Param:  rhs - Reference to Matrix instance.
        ///  Return: Returns output stream.
        ////////////////////////////////////////////////////////////////
        friend ostream& operator<<(ostream& out, const Matrix<T>& rhs)
        {
            stringstream ss;
            ss.precision(3);
            
            for(unsigned int i = 0; i < rhs.m_rows; i++)
            {
                ss << "|";
                for(unsigned int j = 0; j <rhs.m_cols; j++)
                {
                    ss.fill(' ');
                    ss.width(10);
                    ss << right << fixed << rhs(i,j);
                }
                ss << "     |\n";
            }
            
            out << ss.str();
            
            return out;
        }

        ////////////////////////////////////////////////////////////////
        ///  Func:   >> (input)
        ///  Brief:  Overloaded input operator for class.
        ///  Pre:    None.
        ///  Post:   A new Matrix instance is created given user input.
        ///          rhs is set to be equal to the new instance.
        ///  Param:  rhs - Reference to Matrix instance.
        ///  Return: Returns input stream.
        ////////////////////////////////////////////////////////////////
        friend istream& operator>>(istream& in, Matrix<T>& rhs)
        {
            unsigned int rows, cols, k;
            T input;
            
            cout << "Creating a new matrix..." << endl;
            cout << "Enter # of rows: ";
            in >> rows;
            cout << "Enter # of columns: ";
            in >> cols;
            
            Matrix<T> temp(rows,cols);
            cout << endl;
            for(int i = 0; i < rows; i++)
            {
                cout << "Row " << i << ": ";
                k = 0;
                while(k < cols && (in >> input))
                {
                    temp(i,k) = input;
                    k++;
                }
            }
            
            rhs = temp;
            return in;
        }
        
    protected:
        ///////////////////////////////////////////////////////////////
        ///  Func:   getPtr
        ///  Brief:  Access to pointer to data when abstract class is
        ///          passed by reference. 
        ///  Return: Returns pointer to data.
        ////////////////////////////////////////////////////////////////
        virtual T* getPtr() const {return ptr_to_data;} 
        
    private:
    
        unsigned int m_rows;    ///< Number of rows in the Matrix
        unsigned int m_cols;    ///< Number of columns in the Matrix
        unsigned int m_size;    ///< Number of elements in the Matrix
        T* ptr_to_data;         ///< Pointer to the component values
             
        ///////////////////////////////////////////////////////////////
        ///  Func:   copy
        ///  Brief:  Performs a deep copy of the given Matrix
        ///          instance's component values. 
        ///  Pre:    This should only be used after setSize(n) has 
        ///          been called, where n is src.m_size.
        ///  Post:   The component values of *this are set to the 
        ///          component values of src.
        ////////////////////////////////////////////////////////////////   
        void copy(const Matrix<T>& src);
        
};

#include "Matrix.hpp"
#endif //MATRIX_H
