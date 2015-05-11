////////////////////////////////////////////////////////////////
///  Vector.h
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
///  Templated class definition for a mathematical vector data
///  representation. This class is based on the array class
///  described in the Scientific and Engineering C++ book for 
///  this course.
////////////////////////////////////////////////////////////////

#ifndef  VECTOR_H
#define  VECTOR_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include "OutOfRangeErr.h"
#include "IncompatibleVectorErr.h"
using namespace std;

////////////////////////////////////////////////////////////////
///  Class: Vector
///  NOTE: In the function documentation, you will often see
///        '*this' and 'component values' terms. *this is the 
///        term used to refer to the calling object. Component
///        values is the term used to refer to the segments of
///        allocated memory ptr_to_data points to. I don't feel
///        these were the best usage of words but didn't know
///        how to refer to them properly in the documentation.   
////////////////////////////////////////////////////////////////
template <class T>
class Vector
{
    public:
        ////////////////////////////////////////////////////////////////
        ///  Func:   Vector (Default)
        ///  Brief:  Default constructor for class. Creates an empty 
        ///          Vector.
        ///  Pre:    None
        ///  Post:   An empty Vector is defined with size equal to zero
        ///          and no memory allocated.
        ////////////////////////////////////////////////////////////////
        Vector(): m_size(0), ptr_to_data(NULL) {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Vector
        ///  Brief:  Constructor for class. Creates a Vector with n 
        ///          components.
        ///  Pre:    None
        ///  Post:   A Vector is defined with a size equal to n and 
        ///          memory allocated for storing n components, all 
        ///          initialized to zero. 
        ///  Param:  n - Non-negative integer used to define the size 
        ///          of the vector.
        ////////////////////////////////////////////////////////////////
        Vector(unsigned int n);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Vector (Copy)
        ///  Brief:  Copy constructor for class. Creates a new Vector 
        ///          that is a clone of the given Vector.
        ///  Pre:    None
        ///  Post:   A Vector is defined with a size equal to the source
        ///          Vector and with copies of the same components. 
        ///  Param:  src - Another instance of a Vector to be copied.
        ////////////////////////////////////////////////////////////////
        Vector(const Vector<T>& src);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Matrix
        ///  Brief:  Initialization constructor for class. Creates a
        ///          Vector with dimensions based on the sizes of the
        ///          initializer list. Follows this format:
        ///                 { e1, e2, ... eN }
        ///          Size of the Vector is equal to the number of
        ///          elements.
        ///  Pre:    None
        ///  Post:   A Vector is defined with a size equal the number
        ///          of elements in the list. Memory is allocated for
        ///          storing the elements of the list. 
        ///  Param:  lists - Initializer list of instances of a 
        ///          templated type. These values are used to populate 
        ///          the Vector.
        ////////////////////////////////////////////////////////////////
        Vector(initializer_list<T> list);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~Vector (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   Any allocated memory for the class is deallocated.
        ////////////////////////////////////////////////////////////////
        ~Vector();
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   [] (Accessor)
        ///  Brief:  Overloaded accessor operator for class. Allows 
        ///          read access to the components of the Vector. 
        ///  Pre:    i < m_size.
        ///  Post:   None
        ///  Param:  i - Non-negative index value for a Vector 
        ///          component.
        ///  Return: Returns the value stored at the offset memory 
        ///          location from ptr_to_data.
        ////////////////////////////////////////////////////////////////
        T operator[](const unsigned int i) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   [] (Mutator)
        ///  Brief:  Overloaded mutator operator for class. Allows 
        ///          write access to the components of the Vector. 
        ///  Pre:    i < m_size.
        ///  Post:   None
        ///  Param:  i - Non-negative index value for a Vector 
        ///          component.
        ///  Return: Returns the address of the offset memory 
        ///          location from ptr_to_data.
        ////////////////////////////////////////////////////////////////
        T& operator[](const unsigned int i);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   = (Assignment)
        ///  Brief:  Overloaded assignment operator for class. Makes 
        ///          *this a copy of src.
        ///  Pre:    None
        ///  Post:   If src is not *this, memory is reallocated, 
        ///          and m_size and component values are copied from 
        ///          src to *this.
        ///  Param:  src - Another instance of a Vector to be copied.
        ///  Return: Returns reference of self.
        ////////////////////////////////////////////////////////////////
        Vector<T>& operator=(const Vector<T>& src);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   = (Assignment)
        ///  Brief:  Overloaded assignment operator for class. Sets all
        ///          component values to scalar.
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   If any memory has been allocated, the value stored 
        ///          at every memory location is set to scalar.
        ///  Param:  scalar - Instance of template type.
        ///  Return: Returns reference of self.
        ////////////////////////////////////////////////////////////////
        Vector<T>& operator=(const T scalar);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   + (Addition)
        ///  Brief:  Overloaded addition operator for class. 
        ///  Pre:    T = T (assignment) must be defined.
        ///          T + T (addition) must be defined with result T.
        ///  Post:   If Vectors are unequal sizes, an incompatibility 
        ///          error is thrown.
        ///          Otherwise, a new Vector instance of the same size
        ///          is created and component values are the sum of those
        ///          at the same indexes of *this and rhs.
        ///  Param:  rhs - Instance of a Vector.
        ///  Return: Returns the new Vector instance.
        ////////////////////////////////////////////////////////////////
        Vector<T> operator+(const Vector<T>& rhs) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   - (Unary; Negative)
        ///  Brief:  Overloaded subtraction operator for class. Creates
        ///          an instance of the Vector with component values 
        ///          multiplied by -1.
        ///  Pre:    None
        ///  Post:   None
        ///  Return: Returns the new Vector instance.
        ////////////////////////////////////////////////////////////////
        Vector<T> operator-() const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   - (Binary; Subtraction)
        ///  Brief:  Overloaded subtraction operator for class. Creates
        ///          a Matrix instance of *this minus rhs using the
        ///          overloaded + and -(unary) operators for this class.
        ///  Pre:    None
        ///  Post:   None
        ///  Param:  src - Instance of a Vector
        ///  Return: Returns the new Vector instance.
        ////////////////////////////////////////////////////////////////
        Vector<T> operator-(const Vector<T>& src) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Dot product)
        ///  Brief:  Overloaded multiplication operator for class.
        ///          Performs the Dot product on two Vector instances.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T += T (addition) must be defined.
        ///          T * T (multiplication) must be defined with result
        ///          T.
        ///          T = 0 must be a valid assignment.
        ///  Post:   If Vectors are unequal sizes, an incompatibility 
        ///          error is thrown.
        ///          Otherwise, a new T instance is created and is the
        ///          sum of the products of component values at the same
        ///          indexes of *this and rhs.
        ///  Param:  src - Instance of a Vector.
        ///  Return: Returns the new T instance.
        ////////////////////////////////////////////////////////////////
        T operator*(const Vector<T>& src) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Unary, Vector Scaling)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///          Scales the component values of the Vector by
        ///          scalar.
        ///  Pre:    T = T (assignment) must be defined.
        ///          T * T (multiplication) must be defined with result
        ///          T.
        ///  Post:   A new Vector instance of the same size is created 
        ///          and component values are the product of scalar and  
        ///          those at the same indexes of *this and rhs.
        ///  Param:  scalar - T instance for the componets of the Vector
        ///          to be multiplied by.
        ///  Return: Returns the new Vector instance.
        ////////////////////////////////////////////////////////////////
        Vector<T> operator*(const T scalar) const;
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   * (Binary, Vector Scaling)
        ///  Brief:  Overloaded multiplication operator for class. 
        ///          Scales the component values of src by scalar.
        ///  Pre:    None
        ///  Post:   None
        ///  Param:  scalar - T instance for the componets of src to be
        ///          multiplied by.
        ///  Param:  src - Instance of a Vector.
        ///  Return: Returns the new Vector instance.
        ////////////////////////////////////////////////////////////////
        friend Vector<T> operator*(const T scalar, const Vector<T>& src)
        {
            return (src * scalar);
        }
        
        ///////////////////////////////////////////////////////////////
        ///  Func:   getSize
        ///  Brief:  Accesor for the value of m_size.
        ///  Pre:    None
        ///  Post:   None
        ///  Return: Returns the value of m_size.
        ////////////////////////////////////////////////////////////////
        unsigned int getSize() const;
        
        ///////////////////////////////////////////////////////////////
        ///  Func:   setSize
        ///  Brief:  Mutator for the value of m_size and number of 
        ///          components for the Vector.
        ///  Pre:    None
        ///  Post:   If n = 0, deletes the allocated memory, and sets 
        ///          m_size to zero and ptr_to_data to NULL.
        ///          Else if n and m_size are not equal, deletes the 
        ///          allocated memory, sets m_size to n, and allocates
        ///          new memory of size n and sets the values to 0.
        ///          Otherwise, if m_size == n, nothing changes.
        ///  Param:  n - new Vector size.
        ////////////////////////////////////////////////////////////////
        void setSize(const unsigned int n);
        
        ///////////////////////////////////////////////////////////////
        ///  Func:   Row
        ///  Brief:  Swaps the ith and jth element of the Vector. 
        ///  Pre:    T = T (assignment) must be defined.
        ///  Post:   Throws an error if trying to access a non-existent
        ///          row.
        ///  Return: Returns if trying to swap the same element.
        ////////////////////////////////////////////////////////////////
        void Swap(const unsigned int i, const unsigned int j);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   == (Equivalence)
        ///  Brief:  Overloaded equivalence operator for class. 
        ///  Pre:    T == T (equivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Vector.
        ///  Param:  rhs - Instance of a Vector.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
        {
            if(rhs.m_size != lhs.m_size)
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
        ///  Brief:  Overloaded equivalence operator for class. 
        ///  Pre:    T != T (Inequivalence) must be defined.
        ///  Post:   None.
        ///  Param:  lhs - Instance of a Vector.
        ///  Param:  rhs - Instance of a Vector.
        ///  Return: Returns false if unequal row or column sizes or
        ///          unequal elements. Returns true if all elements are
        ///          found to be equal.
        ////////////////////////////////////////////////////////////////
        friend bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
        {
            if(rhs.m_size != lhs.m_size)
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
        ///  Post:   Prints out the Vector's component values in this
        ///          format: [ x_1 x_2 ... x_n ]
        ///  Param:  rhs - Reference to Vector instance.
        ///  Return: Returns output stream.
        ////////////////////////////////////////////////////////////////
        friend ostream& operator<<(ostream& out, const Vector<T>& rhs)
        {
            stringstream ss;
            ss.precision(3);
            
            ss << "<";
            for(unsigned int i = 0; i <rhs.m_size; i++)
            {
                ss.fill(' ');
                ss.width(10);
                ss << right << fixed << rhs[i];
            }
            ss << "     >\n";

            out << ss.str();
            
            return out;
        }

        ////////////////////////////////////////////////////////////////
        ///  Func:   >> (input)
        ///  Brief:  Overloaded input operator for class.
        ///  Pre:    User input must be formated as below:
        ///             T<space>T<space>T<Enter>
        ///          Method for >> T must be defined.
        ///          The last character typed before hitting <Enter> 
        ///          can not be a whitespace. If this happens, type in
        ///          the format for a T value and hit <Enter> again. 
        ///  Post:   rhs is resized to the number of inputs given and
        ///          each component value is set to a input value in
        ///          the respective order they were entered.
        ///  Param:  rhs - Reference to Vector instance.
        ///  Return: Returns input stream.
        ////////////////////////////////////////////////////////////////
        friend istream& operator>>(istream& in, Vector<T>& rhs)
        {
            vector<T>  vec;
            unsigned int size = 0;
            T input;
            while((in.peek()!='\n') && (in >> input))
            {
                vec.push_back(input);
            }
            
            size = vec.size();
            rhs.setSize(size);
            for(unsigned int i = 0; i < size; i++)
            {
                rhs[i] = vec[i];
            }
            return in;
        }
        
        
    private:
        
        unsigned int m_size;    ///< Number of components in the Vector
        T* ptr_to_data;         ///< Pointer to the component values
        
        ///////////////////////////////////////////////////////////////
        ///  Func:   copy
        ///  Brief:  Performs a deep copy of the given Vector
        ///          instance's component values. 
        ///  Pre:    This should only be used after setSize(n) has 
        ///          been called, where n is src.m_size.
        ///  Post:   The component values of *this are set to the 
        ///          component values of src.
        ////////////////////////////////////////////////////////////////
        void copy(const Vector<T>& src);
        
};

#include "Vector.hpp"
#endif //VECTOR_H
