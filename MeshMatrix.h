////////////////////////////////////////////////////////////////
///  MeshMatrix.h
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

#ifndef  MESHMATRIX_H
#define  MESHMATRIX_H

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
///  Class: MeshMatrix  
///     NOTE: In the function documentation, you will often see
///        '*this' and 'component values' terms. *this is the 
///        term used to refer to the calling object. Component
///        values is the term used to refer to the segments of
///        allocated memory ptr_to_data points to. I don't feel
///        these were the best usage of words but didn't know
///        how to refer to them properly in the documentation.
////////////////////////////////////////////////////////////////
template <class T>
class MeshMatrix : public Base_Matrix<T>
{
    public:
        ////////////////////////////////////////////////////////////////
        ///  Func:   MeshMatrix (Default)
        ///  Brief:  Default constructor for class. Creates an empty 
        ///          Matrix.
        ///  Pre:    None
        ///  Post:   An empty Mesh Matrix is defined with size equal to 
        ///          zero and no memory allocated.
        ////////////////////////////////////////////////////////////////
        MeshMatrix();
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   MeshMatrix
        ///  Brief:  Primary constructor for class. Creates a n-by-n 
        ///          Mesh Matrix with components.
        ///  Pre:    None
        ///  Post:   A Mesh Matrix is defined with 'n' rows and columns.
        ///          Memory is allocated for storing n*n components, all 
        ///          initialized to zero. 
        ///  Param:  order - Non-negative integer used to define the  
        ///          number of rows and columns for the matrix.
        ////////////////////////////////////////////////////////////////
        MeshMatrix(const unsigned int mesh_deg);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   MeshMatrix (Copy)
        ///  Brief:  Copy constructor for class. Creates a new Mesh Matrix 
        ///          that is a clone of the given Mesh Matrix.
        ///  Pre:    None
        ///  Post:   A Mesh Matrix is defined with the same order as the 
        ///          source Mesh Matrix and with copies
        ///          of the same components. 
        ///  Param:  src - Another instance of a Mesh Matrix to be copied.
        ////////////////////////////////////////////////////////////////
        MeshMatrix(const MeshMatrix<T>& src);

        ////////////////////////////////////////////////////////////////
        ///  Func:   ~MeshMatrix (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   Any allocated memory for the class is deallocated.
        ////////////////////////////////////////////////////////////////
        ~MeshMatrix(){};
        
        
        ///////////////////// Virtual Functions ////////////////////////
      
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Accessor)
        ///  Brief:  Overloaded accessor operator for class. Allows 
        ///          read access to the components of the Mesh Matrix. 
        ///  Pre:    row < m_order
        ///  Pre:    col < m_order
        ///  Post:   None
        ///  Param:  row - Non-negative index value for a Mesh Matrix 
        ///          row location.
        ///  Param:  col - Non-negative index value for a Mesh Matrix 
        ///          column location.
        ///  Return: Returns the value stored at the offset memory 
        ///          location from ptr_to_data. Offset is:
        ///            row*(2*m_order-row-1)/2+col
        ///          If row > col, return zero.
        ////////////////////////////////////////////////////////////////  
        virtual T operator()(const unsigned int row, const unsigned int col) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Accessor)
        ///  Brief:  Overloaded accessor operator for class. Allows 
        ///          read access to the components of the Mesh Matrix. 
        ///  Pre:    row < m_order
        ///  Pre:    col < m_order
        ///  Post:   None
        ///  Param:  row - Non-negative index value for a Mesh Matrix 
        ///          row location.
        ///  Param:  col - Non-negative index value for a Mesh Matrix 
        ///          column location.
        ///  Return: Returns the value stored at the offset memory 
        ///          location from ptr_to_data. Offset is:
        ///            row*(2*m_order-row-1)/2+col
        ///          If row > col, return zero.
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
        virtual unsigned int getSize() const {return 0;}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   numRows
        ///  Brief:  Access to number of rows of the matrix. 
        ///  Pre:    None.
        ///  Post:   None.
        ///  Return: Returns the number of rows of the matrix.
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
        ///  Func:   Resize
        ///  Brief:  Resizes the Mesh Matrix.
        ///  Post:   Matrix dimensions re-defined.
        ////////////////////////////////////////////////////////////////
        virtual void Resize(const unsigned int rows, const unsigned int cols);
              
        ////////////////////////////////////////////////////////////////
        ///  Func:   getType
        ///  Brief:  Allows systems to know the type of matrix when 
        ///          dealing with an abstract class pointer.
        ///  Pre:    None.
        ///  Post:   None.
        ///  Return: Returns the number of rows of the matrix.
        ////////////////////////////////////////////////////////////////
        virtual MatrixType getType() const {return MESH;}

        ///////////////////// Member Functions /////////////////////////
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Matrix-Vector Multiplication)
        ///  Brief:  Overloaded multiplication operator for class.
        ///          Performs multiplication on a Mesh Matrix and Vector
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
        Vector<T> operator*(const Vector<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   getOrder
        ///  Brief:  Gets the order (# of rows-columns) of the Mesh Matrix
        ///  Return: Returns order of the Mesh Matrix.
        ////////////////////////////////////////////////////////////////
        unsigned int getOrder() const {return m_order;}


        ///////////////////// The Friend Zone //////////////////////////
                  
        ////////////////////////////////////////////////////////////////
        ///  Func:   == (Equivalence)
        ///  Brief:  Overloaded equivalence operator for class. 
        ///  Pre:    T == T (equivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Mesh Matrix.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////     
        friend bool operator==(const MeshMatrix<T>& lhs, const Base_Matrix<T>& rhs)
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
        ///  Param:  lhs - Instance of a Mesh Matrix.
        ///  Param:  rhs - Instance of an abstract Base_Matrix.
        ///  Return: Returns true if unequal row or column sizes or
        ///          unequal elements. Returns false if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const MeshMatrix<T>& lhs, const Base_Matrix<T>& rhs)
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
        ///  Param:  lhs - Instance of a Mesh Matrix.
        ///  Param:  rhs - Instance of a Mesh Matrix.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator==(const MeshMatrix<T>& lhs, const MeshMatrix<T>& rhs)
        {
            if(rhs.m_order != lhs.m_order)
            {
                return false;
            }
            
            return true;
        }
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   != (Inequivalence)
        ///  Brief:  Overloaded inequivalence operator for class. 
        ///  Pre:    T != T (inequivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Mesh Matrix.
        ///  Param:  rhs - Instance of a Mesh Matrix.
        ///  Return: Returns true if unequal row or column sizes or
        ///          unequal elements. Returns false if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const MeshMatrix<T>& lhs, const MeshMatrix<T>& rhs)
        {
            if(rhs.m_order != lhs.m_order)
            {
                return true;
            }
            
            return false;
        }

        ////////////////////////////////////////////////////////////////
        ///  Func:   << (output)
        ///  Brief:  Overloaded output operator for class.
        ///  Pre:    None
        ///  Post:   Prints out the Mesh Matrix's component values in this
        ///          format: | x_11 x_12 ... x_1n |
        ///                    ...
        ///                  | x_n1 x_n2 ... x_nn |
        ///  Param:  rhs - Reference to Mesh Matrix instance.
        ///  Return: Returns output stream.
        ////////////////////////////////////////////////////////////////
        friend ostream& operator<<(ostream& out, const MeshMatrix<T>& rhs)
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
        ///  Post:   A new Mesh Matrix instance is created given user 
        ///          input. rhs is set to be equal to the new instance.
        ///  Param:  rhs - Reference to Mesh Matrix instance.
        ///  Return: Returns input stream.
        ////////////////////////////////////////////////////////////////
        friend istream& operator>>(istream& in, MeshMatrix<T>& rhs)
        {
            //ERROR
            return in;
        }
        
    protected:
        ///////////////////////////////////////////////////////////////
        ///  Func:   getPtr
        ///  Brief:  Access to pointer to data when abstract class is
        ///          passed by reference. 
        ///  Return: Returns pointer to data.
        ////////////////////////////////////////////////////////////////
        virtual T* getPtr() const {return NULL;} 
        
    private:
    
        unsigned int m_mesh_deg;
        unsigned int m_order;
        
};

#include "MeshMatrix.hpp"
#endif //MESHMATRIX_H
