////////////////////////////////////////////////////////////////
///  IM_Solver.h
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
///  Function class definition for calculating the solution for 
///	 a system of equations.
////////////////////////////////////////////////////////////////

template <class T>
Solution<T> IM_Solver::operator()(const Base_Matrix<T>& A, 
                                  const Vector<T>& b,
                                  Vector<T>& XO,
                                  const T TOL,
                                  const unsigned int N,
                                  IterationType IT)
{
    Solution<T> sol;
    sol.init_vec = XO;
    sol.tol = TOL;
    
	switch(IT)
	{
	    case JACOBI:
	        Jacobi_Iteration(A,b,XO,TOL,N,sol);
	        break;
        case GAUSS_SEIDEL:         
	        Gauss_Seidel_Iteration(A,b,XO,TOL,N,sol);
            break;
        default:
            cout << "ERROR" << endl;
            break;
    }
    
	return sol;
}


////////////////////// PRIMARY FUNCTIONS ///////////////////////

template <class T>
void IM_Solver::Jacobi_Iteration(const Base_Matrix<T>& A, 
                                 const Vector<T>& b,
                                 Vector<T>& XO,
                                 const T TOL,
                                 const unsigned int N,
                                 Solution<T>& sol)
{
    unsigned int k = 1, n = b.getSize();
    Vector<T> x(n);
    
    if(A.numCols() != n || A.numRows() != n || XO.getSize() != n)
        throw Incompatible_Vector_Err();
     
    while(k <= N)
    {
        for(unsigned int i = 0; i < n; i++)
        {
            T sum = 0;            
            for(unsigned int j = 0; j < n; j++)
            {
                if(j != i)
                {
                    sum += -A(i,j)*XO[j];
                }
            }
            x[i] = (sum+b[i])/A(i,i);
        }
        
        if(L2_norm(x-XO) < TOL)
        {
            sol.sol_vec = x;
            sol.num_iter = k;
            sol.sol_found = true;
            return;
        }
        k++;
        XO = x;
    }
    sol.num_iter = N;
}

template <class T>
void IM_Solver::Gauss_Seidel_Iteration(const Base_Matrix<T>& A, 
                                       const Vector<T>& b,
                                       Vector<T>& XO,
                                       const T TOL,
                                       const unsigned int N,
                                       Solution<T>& sol)
{
    unsigned int k = 1, n = b.getSize();
    Vector<T> x(n);
    
    if(A.numCols() != n || A.numRows() != n || XO.getSize() != n)
        throw Incompatible_Vector_Err();
     
    while(k <= N)
    {
        for(unsigned int i = 0; i < n; i++)
        {
            T sum = 0;            
            for(unsigned int j = 0; j < n; j++)
            {
                if(j < i)
                {
                    sum += -A(i,j)*x[j];
                }
                else if(j > i)
                {
                    sum += -A(i,j)*XO[j];
                }
            }
            x[i] = (sum+b[i])/A(i,i);
        }
        
        if(L2_norm(x-XO) < TOL)
        {
            sol.sol_vec = x;
            sol.num_iter = k;
            sol.sol_found = true;
            return;
        }
        k++;
        XO = x;
    }
    sol.num_iter = N;
}
 

///////////////////// AUXILIARY FUNCTIONS //////////////////////

template <class T>
T IM_Solver::L2_norm(const Vector<T>& x) const
{
    T norm = 0;
    for(int i = 0, size = x.getSize(); i < size; i++)
    {
        norm += x[i]*x[i];
    }
    norm = sqrt(norm);
    return norm;
}
