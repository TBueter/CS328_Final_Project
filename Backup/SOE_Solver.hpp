////////////////////////////////////////////////////////////////
///  SOE_Solver.h
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
Vector<T> SOE_Solver::operator()(Base_Matrix<T>& A, Vector<T>& b)
{
    Vector<T> solution;
    
	switch(A.getType())
	{
	    case STANDARD:
	        solution = Gaussian_Elimination(A,b);
	        break;
        case UPPERTRIANGULAR:         
	        solution = Back_Substitution(A,b);
            break;
        case LOWERTRIANGULAR:
	        solution = Back_Substitution_Inverse(A,b);
            break;
        case SYMMETRICAL:
	        solution = Cholesky_Decomposition(A,b);
            break;
        case TRIDIAGONAL:
	        solution = Thomas_Algorithm(A,b);
            break;
        case DIAGONAL:
	        solution = Direct_Solve(A,b);
            break;
        default:
            cout << "ERROR" << endl;
            break;
    }
    
	return solution;
}


////////////////////// PRIMARY FUNCTIONS ///////////////////////

template <class T>
Vector<T> SOE_Solver::Gaussian_Elimination(Base_Matrix<T>& A, Vector<T>& b)
{
	unsigned int size = b.getSize(),
				 i,j,k,i_max;

	if(A.numRows() != A.numCols() || A.numCols() != size)
		throw Incompatible_Vector_Err();
	
	for(k = 0; k < size; k++)
	{
		i_max = find_pivot(A,k);
		if(A(i_max,k) == 0) return Vector<T>(b.getSize());

		row_swap(A, k, i_max);
		b.Swap(k, i_max);
		
		T c;
		for(i = k+1; i < size; i++)
		{
			c = A(i,k)/A(k,k);
			A(i,k) = 0;
			for(j = k+1; j < size; j++)
				A(i,j) = A(i,j) - c*A(k,j);
			b[i] = b[i] - c*b[k];
		}
	}
	return Back_Substitution(A,b);
}

template <class T>
Vector<T> SOE_Solver::Back_Substitution(const Base_Matrix<T>& A, const Vector<T>& b)
{
	unsigned int size = b.getSize();
	Vector<T> x(size);
	
	T s;
	for(int i = size - 1; i >= 0; i--)
	{
		s = 0;
		for(int j = i + 1; j < size; j++)
			s += A(i,j)*x[j];
		x[i] = (b[i] - s)/A(i,i);
	}
	
	return x;
}

template <class T>
Vector<T> SOE_Solver::Back_Substitution_Inverse(const Base_Matrix<T>& A, const Vector<T>& b)
{
	unsigned int size = b.getSize();
	Vector<T> x(size);
	
	T s;
	for(int i = 0; i < size; i++)
	{
		s = 0;
		for(int j = 0; j < i; j++)
			s += A(i,j)*x[j];
		x[i] = (b[i] - s)/A(i,i);
	}
	
	return x;
}

template <class T>
Vector<T> SOE_Solver::Direct_Solve(const Base_Matrix<T>& A, const Vector<T>& b)
{
	unsigned int size = b.getSize();
	Vector<T> x(size);

	for(int i = 0; i < size; i++)
	{
		x[i] = b[i]/A(i,i);
	}
	
	return x;
}

template <class T>
Vector<T> SOE_Solver::Thomas_Algorithm(Base_Matrix<T>& A, Vector<T>& b)
{
	unsigned int size = b.getSize();
	Vector<T> x(size);

    T m;
	for(int k = 1; k < size; k++)
	{
		m = A(k,k-1)/A(k-1,k-1);
		A(k,k) -= m*A(k-1,k);
		b[k] -= m*b[k-1];
	}
	
	x[size-1] = b[size-1]/A(size-1,size-1);
	for(int k = size-2; k >= 0; k--)
	{
	    x[k] = (b[k] - A(k,k+1)*x[k+1])/A(k,k);
    }
	
	return x;
}

template <class T>
Vector<T> SOE_Solver::Cholesky_Decomposition(Base_Matrix<T>& A, Vector<T>& b)
{
	unsigned int size = b.getSize();

    T s;
    for(int k = 0; k < size; k++)
    {
        for(int i = 0; i < k; i++)
        {
            s = 0;
            for(int j = 0; j < i; j++)
            {
                s += A(i,j)*A(k,j);
            }
            A(k,i) = (A(k,i) - s)/A(i,i);
        }
        s = 0;
        for(int j = 0; j < k; j++)
        {
            s += A(k,j)*A(k,j);
        }
        A(k,k) = sqrt(A(k,k)-s);
    }
	
	return Back_Substitution(A,Back_Substitution_Inverse(A,b));
}


///////////////////// AUXILIARY FUNCTIONS //////////////////////

template <class T>
unsigned int SOE_Solver::find_pivot(const Base_Matrix<T>& A, unsigned int k)
{
	unsigned int n = A.numRows(), index_max = k;
	T a, max_pivot = abs(A(k,k));
	
	for(unsigned int i = k+1; i < n; i++)
	{
		a = abs(A(i,k));
		if(a > max_pivot)
		{
			max_pivot = a;
			index_max = i;
		}
	}
	return index_max;
}

template <class T>
void SOE_Solver::row_swap(Base_Matrix<T>& A, unsigned int i, unsigned int j)
{	
	if(i == j)
		return;
		
	if(i >= A.numRows() || j >= A.numCols())
		throw Incompatible_Matrix_Err();

	T temp;
	for(unsigned int k = 0, cols = A.numCols(); k < cols; k++)
	{
		temp = A(i,k);
		A(i,k) = A(j,k);
		A(j,k) = temp;
	}
}
