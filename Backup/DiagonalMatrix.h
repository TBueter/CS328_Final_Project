////////////////////////////////////////////////////////////////
///  DiagonalMatrix.h
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
///
///  Programmer :  Travis Bueter
///  Assignment :  An Abstract Matrix Class and Some Derivatives
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
///  Templated class definition for a mathematical upper 
///  triangular matrix data representation. This class is based 
///  on the array class described in the Scientific and 
///  Engineering C++ book for this course. This is a square 
///  Matrix by definition.
////////////////////////////////////////////////////////////////

#ifndef  DIAGONALMATRIX_H
#define  DIAGONALMATRIX_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <initializer_list>
#include "Base_Matrix.h"
#include "Matrix.h"
#include "Vector.h"
#include "OutOfRangeErr.h"
#include "IncompatibleVectorErr.h"
#include "IncompatibleMatrixErr.h"
using namespace std;

////////////////////////////////////////////////////////////////
///  Class: DiagonalMatrix  
///     NOTE: In the function documentation, you will often see
///        '*this' and 'component values' terms. *this is the 
///        term used to refer to the calling object. Component
///        values is the term used to refer to the segments of
///        allocated memory ptr_to_data points to. I don't feel
///        these were the best usage of words but didn't know
///        how to refer to them properly in the documentation.
////////////////////////////////////////////////////////////////
template <class T>
class DiagonalMatrix : public Base_Matrix<T>
{
    public:
        ////////////////////////////////////////////////////////////////
        ///  Func:   DiagonalMatrix (Default)
        ///  Brief:  Default constructor for class. Creates an empty 
        ///          Matrix.
        ///  Pre:    None
        ///  Post:   An empty Diagonal Matrix is defined with size
        ///          equal to zero and no memory allocated.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix();
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   DiagonalMatrix
        ///  Brief:  Primary constructor for class. Creates a n-by-n 
        ///          Diagonal Matrix with components.
        ///  Pre:    None
        ///  Post:   A Diagonal Matrix is defined with 'n' rows and
        ///          columns.
        ///          Memory is allocated for storing n*n components, all 
        ///          initialized to zero. 
        ///  Param:  order - Non-negative integer used to define the  
		///			 number of rows and columns for the matrix.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix(const unsigned int order);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   DiagonalMatrix
        ///  Brief:  Alternate constructor for class. Creates a n-by-n 
        ///          Diagonal Matrix with components
        ///  Pre:    None
        ///  Post:   A Diagonal Matrix is defined with 'n' rows and
        ///          columns.
        ///          Memory is allocated for storing n*n components, all 
        ///          initialized to the given value. 
        ///  Param:  order - Non-negative integer used to define the  
		///			 number of rows and columns for the matrix.
        ///  Param:  value - Instance of template type that all 
        ///          elements of the matrix are set to.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix(const unsigned int order, const T value);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   DiagonalMatrix (Copy)
        ///  Brief:  Copy constructor for class. Creates a new 
        ///          Diagonal Matrix that is a clone of the given    
        ///          Diagonal Matrix.
        ///  Pre:    None
        ///  Post:   A Diagonal Matrix is defined with the same order
        ///          as the source Diagonal Matrix and with copies
        ///          of the same components. 
        ///  Param:  src - Another instance of a Diagonal Matrix to 
        ///          be copied.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix(const DiagonalMatrix<T>& src);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   DiagonalMatrix
        ///  Brief:  Initialization constructor for class. Creates a
        ///          Matrix with dimensions based on the sizes of the
        ///          initializer lists. Follows this format:
        ///                     { {...}, {...}, ... {...} }
        ///          Number of rows 'm' is equal to the number of
        ///          internal brackets. Number of columns 'n' is equal
        ///          to the number of elements of the internal brackets.
        ///  Pre:    The internal brackets, {...}, *should* have the 
        ///          same number of elements. An error will be thrown
        ///          if any differ from the size of the first set.
        ///  Post:   The internal brackets, {...}, should have the 
        ///          same number of elements. An error will be thrown
        ///          if any differ from the size of the first set.
        ///          A Diagonal Matrix is defined with 'm' rows and 
        ///          'n' columns.
        ///          Memory is allocated for storing m*n components, all 
        ///          initialized to the given values. 
        ///  Param:  lists - Initializer list of initializer lists of 
        ///          instances of a templated type. These values are 
        ///          used to populate the Diagonal Matrix.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix(const initializer_list< initializer_list<T> > list);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~DiagonalMatrix (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   Any allocated memory for the class is deallocated.
        ////////////////////////////////////////////////////////////////
        ~DiagonalMatrix();
        
        
        ///////////////////// Virtual Functions ////////////////////////
      
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Accessor)
        ///  Brief:  Overloaded accessor operator for class. Allows 
        ///          read access to the components of the Diagonal 
        ///          Matrix. 
        ///  Pre:    row < m_rows
        ///  Pre:    col < m_cols
        ///  Post:   None
        ///  Param:  row - Non-negative index value for a Diagonal 
        ///          Matrix row location.
        ///  Param:  col - Non-negative index value for a Diagonal 
        ///          Matrix column location.
        ///  Return: Returns the value stored at the offset memory 
        ///          location from ptr_to_data. Offset is:
        ///            row*(2*m_cols-row-1)/2+col
        ///          If row > col, return zero.
        ////////////////////////////////////////////////////////////////  
        virtual T operator()(const unsigned int row, const unsigned int col) const;
      
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Mutator)
        ///  Brief:  Overloaded mutator operator for class. Allows 
        ///          read access to the components of the Diagonal 
        ///          Matrix. 
        ///  Pre:    row < m_order
        ///  Pre:    col < m_order
        ///  Post:   Throws error if row > col.
        ///  Param:  row - Non-negative index value for a Diagonal 
        ///          Matrix row location.
        ///  Param:  col - Non-negative index value for a Diagonal 
        ///          Matrix column location.
        ///  Return: Returns the address at the offset memory 
        ///          location from ptr_to_data. Offset is:
        ///             row*(2*m_order-row-1)/2+col
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
        ///     Return: Returns the size of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual unsigned int getSize() const {return m_size;}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   numRows
        ///  Brief:  Access to number of rows of the matrix. 
        ///  Pre:    None.
        ///  Post:   None.
        ///     Return: Returns the number of rows of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual unsigned int numRows() const {return m_order;}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   numCols
        ///  Brief:  Access to number of columns of the matrix. 
        ///  Pre:    None.
        ///  Post:   None.
        ///  Return: Returns the number of columns of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual unsigned int numCols() const {return m_order;}
              
        ////////////////////////////////////////////////////////////////
        ///  Func:   getType
        ///  Brief:  Allows systems to know the type of matrix when 
        ///          dealing with an abstract class pointer.
        ///  Pre:    None.
        ///  Post:   None.
        ///     Return: Returns the number of rows of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual MatrixType getType() const {return DIAGONAL;}


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
        DiagonalMatrix<T>& operator=(const Base_Matrix<T>& rhs);
                
        ////////////////////////////////////////////////////////////////
        ///  Func:   = (Assignment)
        ///  Brief:  Overloaded assignment operator for class. Makes 
        ///          *this a copy of src.
        ///  Pre:    None
        ///  Post:   If src is not *this, memory is reallocated, 
        ///          and m_size and component values are copied from 
        ///          src to *this.
        ///  Param:  src - Another instance of a Diagonal Matrix to be 
        ///          copied.
        ///  Return: Returns reference of self.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix<T>& operator=(const DiagonalMatrix<T>& rhs);
        
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
        DiagonalMatrix<T>& operator+=(const Base_Matrix<T>& rhs);
          
        ////////////////////////////////////////////////////////////////
        ///  Func:   += (Addition assignment)
        ///  Brief:  Overloaded addition assignment operator for class. 
        ///  Pre:    T += T (addition assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///          Otherwise, component values of *this are summed
        ///          with those of rhs.
        ///  Param:  rhs - Instance of a Diagonal Matrix.
        ///  Return: Returns self.
        //////////////////////////////////////////////////////////////// 
        DiagonalMatrix<T>& operator+=(const DiagonalMatrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   - (Negative)
        ///  Brief:  Overloaded subtraction operator for class. Creates
        ///          an instance of the Matrix with component values 
        ///          multiplied by -1.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T * int (multiplication) must be defined with 
        ///          result T.
        ///  Post:   None
        ///  Return: Returns the new Diagonal Matrix instance.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix<T>  operator-() const;
        
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
        DiagonalMatrix<T>& operator-=(const Base_Matrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   -= (Subtraction assignment)
        ///  Brief:  Overloaded subtraction assignment operator for 
        ///          class. 
        ///  Pre:    T -= T (addition assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///  Param:  rhs - Instance of a Diagonal Matrix.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix<T>& operator-=(const DiagonalMatrix<T>& rhs);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Unary, Matrix Scaling)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///          Scales the component values of the Diagonal Matrix 
        ///          by the scalar.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T * T (multiplication) must be defined with result
        ///          T.
        ///  Post:   A new Matrix instance of the same size is created 
        ///          and component values are the product of scalar.
        ///  Param:  scalar - T instance for the componets of the 
        ///          Diagonal Matrix to be multiplied by.
        ///  Return: Returns the new Diagonal Matrix instance.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix<T>  operator*(const T scalar) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   *= (Urnary, Matrix scaling assignment)
        ///  Brief:  Overloaded multiplication assigment operator for  
        ///          class. Scales the component values of the Diagonal 
        ///          Matrix by the scalar. 
        ///  Pre:    T *= T (multiplication assignment) must be defined.
        ///  Post:   If the Matrices are unequal sizes, an  
        ///          incompatibility error is thrown.
        ///  Param:  scalar - T instance for the componets of the  
        ///          Diagonal Matrix to be multiplied by.
        ///  Return: Returns self.
        ////////////////////////////////////////////////////////////////
        DiagonalMatrix<T>& operator*=(const T scalar);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Matrix-Vector Multiplication)
        ///  Brief:  Overloaded multiplication operator for class.
        ///          Performs multiplication on a Diagonal Matrix and 
        ///          Vector instance.
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
        Vector<T> operator*(const Vector<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Transpose
        ///  Brief:  Takes the transpose of the Diagonal Matrix. 
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   None.
        ///  Return: Returns a new Matrix instance that is a transpose 
        ///          of the Diagonal Matrix.
        ////////////////////////////////////////////////////////////////
        Matrix<T> Transpose() const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   SetAll
        ///  Brief:  Sets all the elements of the Diagonal Matrix to the 
        ///          given value. 
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   All elements set to the given value.
        ////////////////////////////////////////////////////////////////
        void SetAll(T value);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Zero
        ///  Brief:  Sets all the elements of the Diagonal Matrix to 
        ///          zero. 
        ///  Pre:    T = 0 (assignment) must be defined.
        ///  Post:   All elements set to zero.
        ////////////////////////////////////////////////////////////////
        void Zero();

        ////////////////////////////////////////////////////////////////
        ///  Func:   Resize
        ///  Brief:  Deletes the data in the Diagonal Matrix and resizes 
        ///          it.
        ///  Post:   Memory has been deleted, reallocated, and all
        ///          values set to zero.
        ////////////////////////////////////////////////////////////////
        void Resize(const unsigned int order);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   getOrder
        ///  Brief:  Gets the order (# of rows-columns) of the Diagonal 
        ///          Matrix
        ///  Return: Returns order of the Diagonal Matrix.
        ////////////////////////////////////////////////////////////////
        unsigned int getOrder() const {return m_order;}


        ///////////////////// The Friend Zone //////////////////////////
                
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Binary, Matrix Scaling)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///          Scales the component values of src by scalar.
        ///  Pre:    None
        ///  Post:   None
        ///  Param:  scalar - T instance for the componets of src to be
        ///          multiplied by.
        ///  Param:  src - Instance of a Diagonal Matrix.
        ///  Return: Returns the new Diagonal Matrix instance.
        ////////////////////////////////////////////////////////////////
        friend DiagonalMatrix<T> operator*(const T scalar, const DiagonalMatrix<T>& src)
        {
            return (src * scalar);
        }
                  
        ////////////////////////////////////////////////////////////////
        ///  Func:   == (Equivalence)
        ///  Brief:  Overloaded equivalence operator for class. 
        ///  Pre:    T == T (equivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Diagonal Matrix.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////     
        friend bool operator==(const DiagonalMatrix<T>& lhs, const Base_Matrix<T>& rhs)
        {
            if(lhs.m_order != rhs.numRows() || lhs.m_order != rhs.numCols())
            {
                return false;
            }
            
            for(unsigned int i = 0, size = lhs.m_order; i < size; i++)
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
        ///  Param:  lhs - Instance of a Diagonal Matrix.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns true if unequal row or column sizes or
        ///          unequal elements. Returns false if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const DiagonalMatrix<T>& lhs, const Base_Matrix<T>& rhs)
        {
            if(lhs.m_order != rhs.numRows() || lhs.m_order != rhs.numCols())
            {
                return true;
            }
            
            for(unsigned int i = 0, size = lhs.m_order; i < size; i++)
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
        ///  Param:  lhs - Instance of a Diagonal Matrix.
        ///  Param:  rhs - Instance of a Diagonal Matrix.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator==(const DiagonalMatrix<T>& lhs, const DiagonalMatrix<T>& rhs)
        {
            if(rhs.m_order != lhs.m_order)
            {
                return false;
            }

            T* p = lhs.ptr_to_data + lhs.m_size;
            T* q = rhs.ptr_to_data + rhs.m_size;
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
        ///  Param:  lhs - Instance of a Diagonal Matrix.
        ///  Param:  rhs - Instance of a Diagonal Matrix.
        ///  Return: Returns true if unequal row or column sizes or
        ///          unequal elements. Returns false if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const DiagonalMatrix<T>& lhs, const DiagonalMatrix<T>& rhs)
        {
            if(rhs.m_order != lhs.m_order)
            {
                return true;
            }

            T* p = lhs.ptr_to_data + lhs.m_size;
            T* q = rhs.ptr_to_data + rhs.m_size;
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
        ///  Post:   Prints out the Diagonal Matrix's component
        ///          values in this
        ///          format: | x_11 x_12 ... x_1n |
        ///                    ...
        ///                  | x_n1 x_n2 ... x_nn |
        ///  Param:  rhs - Reference to Diagonal Matrix instance.
        ///  Return: Returns output stream.
        ////////////////////////////////////////////////////////////////
        friend ostream& operator<<(ostream& out, const DiagonalMatrix<T>& rhs)
        {
            stringstream ss;
            ss.precision(3);
            
            for(unsigned int i = 0; i < rhs.m_order; i++)
            {
                ss << "|";
                for(unsigned int j = 0; j <rhs.m_order; j++)
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
        ///  Post:   A new Diagonal Matrix instance is created given 
        ///          user input. rhs is set to be equal to the new 
        ///          instance.
        ///  Param:  rhs - Reference to Diagonal Matrix instance.
        ///  Return: Returns input stream.
        ////////////////////////////////////////////////////////////////
        friend istream& operator>>(istream& in, DiagonalMatrix<T>& rhs)
        {
            unsigned int order, k;
            T input;
            
            cout << "Creating a new upper triangular matrix..." << endl;
            cout << "Enter the order: ";
            in >> order;
            
            rhs.Resize(order);
            cout << endl;
            for(int i = 0; i < order; i++)
            {
                cout << "Row " << i << ": ";
                k = i;
                while(k < order && (in >> input))
                {
                    rhs(i,k) = input;
                    k++;
                }
            }
            cout << endl;
                            
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
    
        unsigned int m_order;    ///< Number of rows & columns in the Matrix
        unsigned int m_size;     ///< Number of elements in the Matrix
        T* ptr_to_data;          ///< Pointer to the component values
             
        ///////////////////////////////////////////////////////////////
        ///  Func:   copy
        ///  Brief:  Performs a deep copy of the given Diagonal Matrix
        ///          instance's component values. 
        ///  Pre:    This should only be used after setSize(n) has 
        ///          been called, where n is src.m_size.
        ///  Post:   The component values of *this are set to the 
        ///          component values of src.
        ////////////////////////////////////////////////////////////////  
        void copy(const DiagonalMatrix<T>& src);
        
};

#include "DiagonalMatrix.hpp"
#endif //DIAGONALMATRIX_H