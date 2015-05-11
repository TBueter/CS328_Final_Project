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
        ///  Func:   generate_Matrix
        ///  Brief:  Fills a Matrix with the values for a
        ///          Central-Difference Formula for Order O(h2) based 
        ///          on the given mesh density.
        ///  Pre:    Matrix passed in must be of type 'Matrix<T>' or
        ///          'SymmetricalMatrix<T>'. All other types defined by
        ///          our library will be reject as they can not properly
        ///          represent the problem.
        ///  Post:   'A' has data for problem.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
        ///  Param:  N - Mesh density.
        ////////////////////////////////////////////////////////////////
        template <class T>
        void generate_Matrix(Base_Matrix<T>& A, const unsigned int N);

        ////////////////////////////////////////////////////////////////
        ///  Func:   generate_Vector
        ///  Brief:  Fills a Vector with the values for a
        ///          Central-Difference Formula for Order O(h2) for the
        ///          given mesh density, parameters, and bounding funcs.
        ///  Post:   'b' has data for problem.
        ///  Param:  b - Vector instance. RHS of system of equations.
        ///  Param:  N - Mesh density.
        ///  Param:  p - Parameters for the x & y ranges.
        ///  Param:  xlf - Lower boundary function for x.
        ///  Param:  xuf - Upper boundary function for x.
        ///  Param:  ylf - Lower boundary function for y.
        ///  Param:  yuf - Upper boundary function for y.
        ////////////////////////////////////////////////////////////////              
        template <class T, class T_function>
        void generate_Vector(Vector<T>& b,
                             const unsigned int N,
                             const Parameters<T> p,
                             const T_function xlf,
                             const T_function xuf,
                             const T_function ylf,
                             const T_function yuf);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   generate_Axes
        ///  Brief:  Fills Vectors with the axes values of the mesh for 
        ///          a Central-Difference Formula for Order O(h2) for 
        ///          the given mesh density and parameters.
        ///  Post:   'x_axis' and 'y_axis' have data for problem.
        ///  Param:  x_axis - Vector instance.
        ///  Param:  y_axis - Vector instance.
        ///  Param:  N - Mesh density.
        ///  Param:  p - Parameters for the x & y ranges.
        ////////////////////////////////////////////////////////////////  
        template <class T>                 
        void generate_Axes(Vector<T>& x_axis,
                           Vector<T>& y_axis,
                           const unsigned int N,
                           const Parameters<T> p);

        ////////////////////////////////////////////////////////////////
        ///  Func:   generate_Solution
        ///  Brief:  Fills Vectors with actual values for a 
        ///          Central-Difference Formula for Order O(h2) for the 
        ///          given mesh density, parameters, and solution func.
        ///  Post:   'sol' has actual values
        ///  Param:  sol - Vector instance.
        ///  Param:  N - Mesh density.
        ///  Param:  p - Parameters for the x & y ranges.
        ///  Param:  f - Solution function.
        ////////////////////////////////////////////////////////////////            
        template <class T, class T_function>
        void generate_Solution(Vector<T>& sol, 
                               const unsigned int N, 
                               const Parameters<T> p,
                               const T_function f);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Special_Solver
        ///  Brief:  Solves Possion's equation using the 
        ///          Central-Difference Formula for Order O(h2) without
        ///          the need to generate a Matrix. This is based on the
        ///          Gauss-Seidel iterative method.
        ///  Pre:    None
        ///  Param:  b - Vector instance. RHS of system of equations.
        ///  Param:  XO - Vector instance. Initial guess. 
        ///  Param:  TOL - Tolerance
        ///  Param:  Limit - Iteration limit.
        ////////////////////////////////////////////////////////////////
        template <class T>             
        Vector<T> Special_Solver(const Vector<T>& b,
                                 Vector<T>& XO,
                                 const T TOL,
                                 const unsigned int Limit);          

    private:
    
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
        T L2_norm(const Vector<T>& x);
};

#include "Central_Diff_Oh2.hpp"
#endif //CENTRAL_DIFF_OH2_H
