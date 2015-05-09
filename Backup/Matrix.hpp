////////////////////////////////////////////////////////////////
///  Matrix.hpp
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
///  Templated class definition for a mathematical matrix data
///  representation. This class is based on the array class
///  described in the Scientific and Engineering C++ book for 
///  this course.
////////////////////////////////////////////////////////////////

//For Matrix[Rows][Cols]: A[i][j] == A[m_cols*i+j]

//////////// Constructs ///////////
template <class T>
Matrix<T>::Matrix()
{
    m_rows = 0;
    m_cols = 0;
	m_size = 0;
    ptr_to_data = NULL;
}

template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_size = m_rows*m_cols;
	ptr_to_data = new T[m_size];
	
	Zero();
}

template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, T value)
{
	m_rows = rows;
	m_cols = cols;
	m_size = m_rows*m_cols;
	ptr_to_data = new T[m_size];
	
	SetAll(value);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& src)
{   
    cout << "HERE" << endl;
	m_rows = src.m_rows;
	m_cols = src.m_cols;
	m_size = m_rows*m_cols;
	ptr_to_data = new T[m_size];
	copy(src);
}

template <class T>
Matrix<T>::Matrix(initializer_list< initializer_list<T> > list)
{
	m_rows = list.size();
	typename initializer_list< initializer_list<T> >::iterator it = list.begin();
	m_cols = it[0].size();
	m_size = m_rows*m_cols;
	ptr_to_data = new T[m_size];
	unsigned int k = 0;
	for(auto i : list)
	{
		if(i.size() != m_cols)
			throw Out_Of_Range_Err(i.size());
		for(auto j : i)
		{
			ptr_to_data[k++] = j;
		}
	}
}

template <class T>
Matrix<T>::~Matrix()
{
	if(ptr_to_data != NULL)
	{
		delete [] ptr_to_data;
	}
}

//////// Virtual functions ////////
template <class T>
T Matrix<T>::operator()(const unsigned int row, const unsigned int col) const
{
	if(row >= m_rows || col >= m_cols)
	{
        throw Out_Of_Range_Err(m_cols*row+col);
	}
	
	return ptr_to_data[m_cols*row+col];
}

template <class T>
T& Matrix<T>::operator()(const unsigned int row, const unsigned int col)
{
	if(row >= m_rows || col >= m_cols)
	{
        throw Out_Of_Range_Err(m_cols*row+col);
	}
		
	return ptr_to_data[m_cols*row+col];
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Base_Matrix<T>& rhs) const
{
    if(rhs.numRows() != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	unsigned int cols = rhs.numCols();
	
	Matrix<T> C(m_rows,cols);
	T* p = ptr_to_data + m_size;
	
	T sum;
	for(int i = C.numRows()-1; i >= 0; i--)
	{
		for(int j = C.numCols()-1; j >= 0; j--)
		{
			sum = 0;
			for(int k = m_cols-1; k >= 0; k--)
			{
				sum += *--p * rhs(k,j);
			}
			C(i,j) = sum;
			p += m_cols-i;
		}
		p -= m_cols-i;
	}
	
	return C;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Base_Matrix<T>& rhs) const
{
	if(rhs.numRows() != m_rows || rhs.numCols() != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	Matrix<T> sum(m_rows, m_cols);
	T* p = ptr_to_data + m_size;
	
	for(int i = m_rows-1; i >= 0; i--)
	{
		for(int j = m_cols-1; j >= 0; j--)
		{
			sum(i,j) = *--p + rhs(i,j);
		}
	}
	
	return sum;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Base_Matrix<T>& rhs) const
{
	if(rhs.numRows() != m_rows || rhs.numCols() != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	Matrix<T> diff(m_rows, m_cols);
	T* p = ptr_to_data + m_size;
	
	for(int i = m_rows-1; i >= 0; i--)
	{
		for(int j = m_cols-1; j >= 0; j--)
		{
			diff(i,j) = *--p - rhs(i,j);
		}
	}
	
	return diff;
}

template <class T>
void Matrix<T>::Resize(const unsigned int rows, const unsigned int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_size = rows*cols;
	if(ptr_to_data != NULL)
	    delete [] ptr_to_data;
	ptr_to_data = new T[m_size];
	
	Zero();
}

///////// Member functions ////////
template <class T>
Matrix<T>& Matrix<T>::operator=(const Base_Matrix<T>& rhs)
{
    T* rhs_ptd = rhs.getPtr();
    if(ptr_to_data != rhs_ptd && rhs_ptd != NULL)
    {
        m_rows = rhs.numRows();
        m_cols = rhs.numCols();
        m_size = m_rows*m_cols;
        delete [] ptr_to_data;
        ptr_to_data = new T[m_size];
		
		T* p = ptr_to_data + m_size;
        
        for(int i = m_rows-1; i >= 0; i--)
        {
            for(int j = m_cols-1; j >= 0; j--)
            {
                *--p = rhs(i,j);
            }
        }
    }
    else if(rhs_ptd == NULL)
    {
        m_rows = 0;
        m_cols = 0;
        m_size = 0;
        delete [] ptr_to_data;
        ptr_to_data = NULL;
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if(ptr_to_data != rhs.ptr_to_data)
	{
		m_rows = rhs.m_rows;
		m_cols = rhs.m_cols;
		m_size = m_rows*m_cols;
		delete [] ptr_to_data;
		ptr_to_data = new T[m_size];
		copy(rhs);
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Base_Matrix<T>& rhs)
{
	if(rhs.numRows() != m_rows || rhs.numCols() != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	T* p = ptr_to_data + m_size;
	
	for(int i = m_rows-1; i >= 0; i--)
	{
		for(int j = m_cols-1; j >= 0; j--)
		{
            *--p += rhs(i,j);
		}
	}
	
	return *this;  
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
	if(rhs.m_rows != m_rows || rhs.m_cols != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	T* p = ptr_to_data + m_size;
	T* q = rhs.ptr_to_data + m_size;
	while(p > ptr_to_data) *--p += *--q;
	
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const
{
	Matrix<T> neg(m_rows, m_cols);
	
	T* s = neg.ptr_to_data + m_size;
	T* p = ptr_to_data + m_size;
	while(s > neg.ptr_to_data) *--s = *--p * -1;
	
	return neg;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Base_Matrix<T>& rhs)
{
	if(rhs.numRows() != m_rows || rhs.numCols() != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	T* p = ptr_to_data + m_size;
	
	for(int i = m_rows-1; i >= 0; i--)
	{
		for(int j = m_cols-1; j >= 0; j--)
		{
            *--p -= rhs(i,j);
		}
	}
	
	return *this;  
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs)
{
	if(rhs.m_rows != m_rows || rhs.m_cols != m_cols)
	{
		throw Incompatible_Matrix_Err();
	}
	
	T* p = ptr_to_data + m_size;
	T* q = rhs.ptr_to_data + m_size;
	while(p > ptr_to_data) *--p -= *--q;
	
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T scalar) const
{
	Matrix<T> scaled(m_rows, m_cols);
	
	T* s = scaled.ptr_to_data + m_size;
	T* p = ptr_to_data + m_size;
	while(s > scaled.ptr_to_data) *--s = *--p * scalar;
	
	return scaled;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T scalar)
{
	T* p = ptr_to_data + m_size;
	while(p > ptr_to_data) *--p *= scalar;
	
	return *this;
}

template <class T>
Vector<T> Matrix<T>::operator*(const Vector<T>& rhs) const
{
	unsigned int size = rhs.getSize();
	
	if(size != m_cols)
	{
		throw Incompatible_Vector_Err();
	}
	
	Vector<T> b(m_rows);
	
	T sum;
	for(int i = m_rows-1; i >= 0; i--)
	{
		sum = 0;
		for(int j = size-1; j >= 0; j--)
		{
			sum += *(ptr_to_data+(m_cols*i+j)) * rhs[j];
		}
		b[i] = sum;
	}
	
	return b;
}

template <class T>
Matrix<T> Matrix<T>::Transpose() const
{
	Matrix<T> transpose(m_cols, m_rows);
	
	unsigned int len = m_size;
	T* o = ptr_to_data;
	T* t = transpose.ptr_to_data + len;
	while(t > transpose.ptr_to_data)
	{
		len--;
		*--t = *(o+(m_cols*(len%m_rows)+(len/m_rows)));
	}
	
	return transpose;
}

template <class T>
void Matrix<T>::Row_Swap(unsigned int i, unsigned int j)
{
	if(i >= m_rows || j >= m_rows)
		throw Incompatible_Matrix_Err();
	
	if(i == j)
		return;
	
	T temp;
	for(unsigned int k = 0; k < m_cols; k++)
	{
		temp = *(ptr_to_data + (m_cols*i+k));
		*(ptr_to_data + (m_cols*i+k)) = *(ptr_to_data + (m_cols*j+k));
		*(ptr_to_data + (m_cols*j+k)) = temp;
	}
}

template <class T>
void Matrix<T>::SetAll(T value)
{
	for(unsigned int i = 0; i < m_size; i++)
	{
		ptr_to_data[i] = value;
	}
}

template <class T>
void Matrix<T>::Zero()
{
	for(unsigned int i = 0; i < m_size; i++)
	{
		ptr_to_data[i] = 0;		
	}
}

//Copy Matrix Elements (Private)
template <class T>
void Matrix<T>::copy(const Matrix<T>& src)
{
    if(src.ptr_to_data != NULL)
	{
		T* p = ptr_to_data + m_size;
		T* q = src.ptr_to_data + src.m_size;
		while(p > ptr_to_data) *--p = *--q;
	}
	else
	{
		ptr_to_data = NULL;
	}
}
