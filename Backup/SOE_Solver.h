////////////////////////////////////////////////////////////////
///  SOE_Solver.h
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
///	 a system of equations.
////////////////////////////////////////////////////////////////

#ifndef  SOE_SOLVER_H
#define  SOE_SOLVER_H

#include <vector>
#include <cmath>
#include "Matrix.h"
#include "Vector.h"
#include "IncompatibleVectorErr.h"
using namespace std;

////////////////////////////////////////////////////////////////
///  Class: SOE_Solver
///  Brief: Functor for calculating the solution for a system
///			of equations.
////////////////////////////////////////////////////////////////
class SOE_Solver
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   SOE_Solver (Default)
        ///  Brief:  Default constructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        SOE_Solver() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   ~SOE_Solver (Default)
        ///  Brief:  Default deconstructor for class.
        ///  Pre:    None
        ///  Post:   None
        ////////////////////////////////////////////////////////////////
        ~SOE_Solver() {}
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   () (Parenthesis)
        ///  Brief:  Overloaded parenthesis operator for class. Allows 
        ///          class object to be treated as a function. Function
        ///          uses gaussian elimination and back-substitution to
		///			 solve a system of equations.
        ///  Pre:    System of equations must have a definite solution.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns an instance of a Vector that represents
		///			 the solution for the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> operator()(Base_Matrix<T>& A, Vector<T>& b);
        
    private:
        
        ////////////////////// PRIMARY FUNCTIONS ///////////////////////
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Gaussian_Elimination
        ///  Brief:  Implementation of Gaussian Elimination.
        ///  Pre:    T = 0 must be a valid assignment.
		///			 T = T must be defined.
		///			 T - T must be defined with a result T.
		///			 T * T must be defined with a result T.
		///			 T / T must be defined with a result T.
		///			 T == T must be defined with a result bool.
		///			 System of equations must have a definite solution.
        ///  Post:   Throws a incompatible Vector error if the size of
		///          Vector used with the Matrix are not equal.
		///			 A and b are in row echelon form if the system is
		///			 not found to be singular.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns true if the system is found to be singular.
		///			 Returns false otherwise.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> Gaussian_Elimination(Base_Matrix<T>& A, Vector<T>& b);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Back_Substitution
        ///  Brief:  Implementation of Back-substitution.
        ///  Pre:    T = 0 must be a valid assignment.
		///			 T = T must be defined.
		///			 T + T must be defined with a result T.
		///			 T - T must be defined with a result T.
		///			 T * T must be defined with a result T.
		///			 T / T must be defined with a result T.
		///			 A is an Upper Triangular matrix.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns the solution of the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> Back_Substitution(const Base_Matrix<T>& A, const Vector<T>& b);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Forward_Substitution
        ///  Brief:  Implementation of Back-substitution for LT Matrix.
        ///  Pre:    T = 0 must be a valid assignment.
		///			 T = T must be defined.
		///			 T + T must be defined with a result T.
		///			 T - T must be defined with a result T.
		///			 T * T must be defined with a result T.
		///			 T / T must be defined with a result T.
		///			 A is a Lower Triangular matrix.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns the solution of the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> Forward_Substitution(const Base_Matrix<T>& A, const Vector<T>& b);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Direct_Solve
        ///  Brief:  Directly solves a system with a diagonal matrix.
        ///  Pre:    T / T must be defined with a result T.
		///			 A is a diagonal matrix.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns the solution of the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> Direct_Solve(const Base_Matrix<T>& A, const Vector<T>& b);
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Thomas_Algorithm
        ///  Brief:  Implementation of the Thomas Algorithm for a 
        ///          Tridiagonal Matrix.
        ///  Pre:    T = 0 must be a valid assignment.
		///			 T = T must be defined.
		///			 T + T must be defined with a result T.
		///			 T - T must be defined with a result T.
		///			 T * T must be defined with a result T.
		///			 T / T must be defined with a result T.
		///			 A is a Tridiagonal Matrix.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns the solution of the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> Thomas_Algorithm(Base_Matrix<T>& A, Vector<T>& b);
                
        ////////////////////////////////////////////////////////////////
        ///  Func:   Cholesky_Decomposition
        ///  Brief:  Implementation of the Cholesky_Decomposition for a
        ///          Symmetrical Matrix.
        ///  Pre:    T = 0 must be a valid assignment.
		///			 T = T must be defined.
		///			 T + T must be defined with a result T.
		///			 T - T must be defined with a result T.
		///			 T * T must be defined with a result T.
		///			 T / T must be defined with a result T.
		///			 A is a symmetrical matrix.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param:  b - Vector instance. RHS of the system of equations.
        ///  Return: Returns the solution of the system of equations.
        ////////////////////////////////////////////////////////////////
        template <class T>
        Vector<T> Cholesky_Decomposition(Base_Matrix<T>& A, Vector<T>& b);
		
		
		///////////////////// AUXILIARY FUNCTIONS //////////////////////
	
        ////////////////////////////////////////////////////////////////
        ///  Func:   find_pivot
        ///  Brief:  Finds the max pivot point of the matrix for the
		///			 given column.
        ///  Pre:    abs(T) must be defined with a result T.
		///			 T = T must be defined.
        ///  Post:   None.
        ///  Param:  A - Matrix instance. LHS of the system of equations.
		///	 Param: k - Column to search for the max pivot in.
        ///  Return: Returns the index of the max pivot.
        ////////////////////////////////////////////////////////////////
		template <class T>
		unsigned int find_pivot(const Base_Matrix<T>& A, unsigned int k);
			
		////////////////////////////////////////////////////////////////
        ///  Func:   Row_Swap
        ///  Brief:  Swaps two specified rows in the matrix.
        ///  Pre:    The given matrix type must be allowed to swap rows.
        ///          Currently, only the basic matrix type can be row
        ///          swapped.
        ///  Post:   Matrix has rows i and j swapped.
        ///  Param:  A - Matrix instance.
		///	 Param:  i - Row to be swapped.
		///  Param:  j - Other row to be swapped.
        ////////////////////////////////////////////////////////////////
		template <class T>
		void row_swap(Base_Matrix<T>& A, unsigned int i, unsigned int j);
};

#include "SOE_Solver.hpp"
#endif //SOE_SOLVER_H
