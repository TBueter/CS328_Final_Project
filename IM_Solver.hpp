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
///  a system of equations using iterative methods.
////////////////////////////////////////////////////////////////

template <class T>
Vector<T> IM_Solver::operator()(const Base_Matrix<T>& A, 
                                const Vector<T>& b,
                                Vector<T>& XO,
                                const T TOL,
                                const unsigned int Limit,
                                IterationType IT)
{
    Vector<T> solution(0);
    
    switch(IT)
    {
        case JACOBI:
            solution = Jacobi_Iteration(A,b,XO,TOL,Limit);
            break;
        case GAUSS_SEIDEL:         
            solution = Gauss_Seidel_Iteration(A,b,XO,TOL,Limit);
            break;
        default:
            cout << "ERROR" << endl;
            break;
    }
    
    return solution;
}


////////////////////// PRIMARY FUNCTIONS ///////////////////////

template <class T>
Vector<T> IM_Solver::Jacobi_Iteration(const Base_Matrix<T>& A, 
                                      const Vector<T>& b,
                                      Vector<T>& XO,
                                      const T TOL,
                                      const unsigned int Limit)
{
    unsigned int k = 1, n = b.getSize();
    Vector<T> x(n);
    
    if(A.numCols() != n || A.numRows() != n || XO.getSize() != n)
        throw Incompatible_Vector_Err();
     
    while(k <= Limit)
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
            return x;
        }
        k++;
        XO = x;
    }
    return Vector<T>(0);
}

template <class T>
Vector<T> IM_Solver::Gauss_Seidel_Iteration(const Base_Matrix<T>& A, 
                                            const Vector<T>& b,
                                            Vector<T>& XO,
                                            const T TOL,
                                            const unsigned int Limit)
{
    unsigned int k = 1, n = b.getSize();
    Vector<T> x(n);
    
    if(A.numCols() != n || A.numRows() != n || XO.getSize() != n)
        throw Incompatible_Vector_Err();
     
    while(k <= Limit)
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
            return x;
        }
        k++;
        XO = x;
    }
    return Vector<T>(0);
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
