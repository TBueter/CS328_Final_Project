////////////////////////////////////////////////////////////////
///  Central_Diff_Oh2.h
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
///  Function class definition for calculating the solution for 
///  a system of equations.
////////////////////////////////////////////////////////////////

#ifndef  CENTRAL_DIFF_OH2_H
#define  CENTRAL_DIFF_OH2_H

#include <vector>
#include <iostream>
#include <cmath>
#include "Base_Matrix.h"
#include "Vector.h"
#include "IncompatibleVectorErr.h"
using namespace std;

//Container for the x & y bounds
template <class T>
struct Parameters
{
    T xlb; //x lower bound
    T xub; //x upper bound
    T ylb; //y lower bound
    T yub; //y upper bound
};

////////////////////////////////////////////////////////////////
///  Class: Central_Diff_Oh2
///  Brief: Functor for calculating the solution for a system
///         of equations.
////////////////////////////////////////////////////////////////
class Central_Diff_Oh2
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Central_Diff_Oh2 (Default)
        ///  Brief:  Default constructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        Central_Diff_Oh2() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~Central_Diff_Oh2 (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        ~Central_Diff_Oh2() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Parenthesis)
        ///  Brief:  Overloaded parenthesis operator for class. Allows 
        ///          class object to be treated as a function. Function
        ///          uses gaussian elimination and back-substitution to
        ///          solve a system of equations.
        ///  Pre:    System of equations must have a definite solution.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
        ///  Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns an instance of a Vector that represents
        ///          the solution for the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        void generate_Matrix(Base_Matrix<T>& A, const unsigned int N);
                        
        template <class T, class T_function>
        void generate_Vector(Vector<T>& b,
                             const unsigned int N,
                             const Parameters<T> p,
                             const T_function xlf,
                             const T_function xuf,
                             const T_function ylf,
                             const T_function yuf);
        
        template <class T>                 
        void generate_Axes(Vector<T>& x_axis,
                           Vector<T>& y_axis,
                           const unsigned int N,
                           const Parameters<T> p);
                           
        template <class T, class T_function>
        void generate_Solution(Vector<T>& sol, 
                               const unsigned int N, 
                               const Parameters<T> p,
                               const T_function f);
        
        template <class T>             
        Vector<T> Special_Solver(const Vector<T>& b,
                                 Vector<T>& XO,
                                 const T TOL,
                                 const unsigned int Limit);          

    private:
        template <class T>
        T L2_norm(const Vector<T>& x);
};

#include "Central_Diff_Oh2.hpp"
#endif //CENTRAL_DIFF_OH2_H
