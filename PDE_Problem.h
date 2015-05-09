////////////////////////////////////////////////////////////////
///  PDE_Problem.h
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

#ifndef  PDE_PROBLEM_H
#define  PDE_PROBLEM_H

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
///  Class: PDE_Problem
///  Brief: Functor for calculating the solution for a system
///         of equations.
////////////////////////////////////////////////////////////////
class PDE_Problem
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   PDE_Problem (Default)
        ///  Brief:  Default constructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        PDE_Problem() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~PDE_Problem (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        ~PDE_Problem() {}
        
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
        template <class T, typename F>
        void operator()(Base_Matrix<T>& A, 
                        Vector<T>& b,
                        const unsigned int N,
                        const Parameters<T> p,
                        const F xlf,
                        const F xuf,
                        const F ylf,
                        const F yuf);
};

#include "PDE_Problem.hpp"
#endif //PDE_PROBLEM_H
