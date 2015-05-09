////////////////////////////////////////////////////////////////
///  IM_Solver.h
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
///     a system of equations using iterative methods.
////////////////////////////////////////////////////////////////

#ifndef  IM_SOLVER_H
#define  IM_SOLVER_H

#include <cmath>
#include <iostream>
#include "Base_Matrix.h"
#include "Vector.h"
#include "IncompatibleVectorErr.h"
using namespace std;

//Container for the solution. This is used since 
template <class T>
struct Solution {
    bool sol_found = false;
    Vector<T> sol_vec;
    Vector<T> init_vec;
    T tol = 0;
    unsigned int num_iter = 0;
};

template <class T>
ostream& operator<<(ostream& out, const Solution<T>& s)
{
    if(!s.sol_found)
    {
        out << "No solution found in " << s.num_iter << " iterations!"
            << endl;
        out << "Initial Vector: " << s.init_vec << endl;
        out << "Tolerance used: " << s.tol << endl;
    }
    else
    {
        out << "Solution:       " << s.sol_vec << endl;
        out << "Initial Vector: " << s.init_vec << endl;
        out << "Iter. required: " << s.num_iter << endl;
        out << "Tolerance used: " << s.tol << endl;
    }
    return out;
}       

//Used to determine which iterative method the user wants to use.
enum IterationType
{
    JACOBI = 0,
    GAUSS_SEIDEL,
};

////////////////////////////////////////////////////////////////
///  Class: IM_Solver
///  Brief: Functor for calculating the solution for a system
///         of equations using iterative methods.
////////////////////////////////////////////////////////////////
class IM_Solver
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   IM_Solver (Default)
        ///  Brief:  Default constructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        IM_Solver() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~IM_Solver (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        ~IM_Solver() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Parenthesis)
        ///  Brief:  Overloaded parenthesis operator for class. Allows 
        ///          class object to be treated as a function. Function
        ///          allows the use of defined iterative methods to
        ///          solve a system of equations.
        ///  Pre:    System of equations must have a definite solution.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
        ///  Param:  b - Vector instance. RHS of the system of equations.
        ///  Param:  XO  - Initial 'x' vector solution.
        ///  Param:  TOL - Tolerance variable for acceptance.
        ///  Param:  N   - Max number of iterations allowed for finding
        ///          a solution.
        ///  Param:  IT  - Iteration type to be used.
        ///  Return: Returns a struct containing the el.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> operator()(const Base_Matrix<T>& A, 
                             const Vector<T>& b,
                             Vector<T>& XO,
                             const T TOL,
                             const unsigned int N,
                             IterationType IT);
        
    private:
        
        ////////////////////// PRIMARY FUNCTIONS ///////////////////////
        
        
        template <class T>
        Vector<T> Jacobi_Iteration(const Base_Matrix<T>& A, 
                                   const Vector<T>& b,
                                   Vector<T>& XO,
                                   const T TOL,
                                   const unsigned int N);
                                     
        template <class T>
        Vector<T> Gauss_Seidel_Iteration(const Base_Matrix<T>& A, 
                                         const Vector<T>& b,
                                         Vector<T>& XO,
                                         const T TOL,
                                         const unsigned int N);
                                     
        ///////////////////// AUXILIARY FUNCTIONS //////////////////////
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   L2_norm
        ///  Brief:  Calculates the L2 Norm of a Vector.
        ///  Pre:    T = 0 must be a valid assignment.
        ///          T += T must be defined.
        ///          T * T must be defined with a result T.
        ///          sqrt(T) must be defined with a result T.
        ///  Post:   None
        ///  Return: Returns the calculated norm value.
        ////////////////////////////////////////////////////////////////
        template <class T>
        T L2_norm(const Vector<T>& x) const;
};

#include "IM_Solver.hpp"
#endif //IM_SOLVER_H
