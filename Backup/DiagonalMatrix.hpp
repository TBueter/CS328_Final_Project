////////////////////////////////////////////////////////////////
///  DiagonalMatrix.hpp
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
///  Templated class definition for a mathematical diagonal
///  matrix data representation. This class is based 
///  on the array class described in the Scientific and 
///  Engineering C++ book for this course.
////////////////////////////////////////////////////////////////

//////////// Constructs ///////////
template <class T>
DiagonalMatrix<T>::DiagonalMatrix()
{
    m_order = 0;
    m_size = 0;
    ptr_to_data = NULL;
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const unsigned int order)
{
    m_order = order;
    m_size = order;
    ptr_to_data = new T[m_size];
    
    Zero();
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const unsigned int order, const T value)
{
    m_order = order;
    m_size = order;
    ptr_to_data = new T[m_size];
    
    SetAll(value);
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T>& src)
{
    m_order = src.m_order;
    m_size = src.m_size;
    ptr_to_data = new T[m_size];
    
    copy(src);
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const initializer_list< initializer_list<T> > list)
{
    m_order = list.size();
    typename initializer_list< initializer_list<T> >::iterator it = list.begin();
    m_size = m_order;
    ptr_to_data = new T[m_size];
    unsigned int k = 0;
    for(auto i : list)
    {
        for(auto j : i)
        {
            ptr_to_data[k++] = j;
        }
    }
}

template <class T>
DiagonalMatrix<T>::~DiagonalMatrix()
{
    if(ptr_to_data != NULL)
    {
        delete [] ptr_to_data;
    }
}

//////// Virtual functions ////////
template <class T>
T DiagonalMatrix<T>::operator()(const unsigned int row, const unsigned int col) const
{
    if(row >= m_order || col >= m_order)
    {
        throw Out_Of_Range_Err(m_order*row+col);
    }
    
    if(row != col)
        return 0;
    else
        return ptr_to_data[row];
}

template <class T>
T& DiagonalMatrix<T>::operator()(const unsigned int row, const unsigned int col)
{
    if(row >= m_order || col >= m_order)
    {
        throw Out_Of_Range_Err(m_order*row+col);
    }
    
    if(row != col)
        throw Out_Of_Range_Err(m_order*row+col); //BadAccessError();
    else
        return ptr_to_data[row];
}

template <class T>
Matrix<T> DiagonalMatrix<T>::operator*(const Base_Matrix<T>& rhs) const
{
    if(rhs.numRows() != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    unsigned int cols = rhs.numCols();
    
    Matrix<T> C(m_order,cols);
 
    for(int i = m_order-1; i >= 0; i--)
    {
        for(int j = cols-1; j >= 0; j--)
        {
            C(i,j) = *(ptr_to_data + j) * rhs(i,j);
        }
    }
    
    return C;
}

template <class T>
Matrix<T> DiagonalMatrix<T>::operator+(const Base_Matrix<T>& rhs) const
{
    if(rhs.numRows() != m_order || rhs.numCols() != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    Matrix<T> sum(m_order, m_order);
    
    for(int i = m_order-1; i >= 0; i--)
    {
        for(int j = m_order-1; j >= 0; j--)
        {
            if(i != j)
                sum(i,j) = rhs(i,j);
            else
                sum(i,j) = *(ptr_to_data + j) + rhs(i,j);
        }
    }
    
    return sum;
}

template <class T>
Matrix<T> DiagonalMatrix<T>::operator-(const Base_Matrix<T>& rhs) const
{
    if(rhs.numRows() != m_order || rhs.numCols() != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    Matrix<T> diff(m_order, m_order);
    
    for(int i = m_order-1; i >= 0; i--)
    {
        for(int j = m_order-1; j >= 0; j--)
        {
            if(i != j)
                diff(i,j) = -rhs(i,j);
            else
                diff(i,j) = *(ptr_to_data + j) - rhs(i,j);
        }
    }
    
    return diff;
}

///////// Member functions ////////
template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator=(const Base_Matrix<T>& rhs)
{
    if(rhs.numRows() != rhs.numCols())
        throw Incompatible_Matrix_Err();
    
    T* rhs_ptd = rhs.getPtr();
    if(ptr_to_data != rhs_ptd && rhs_ptd != NULL)
    {
        m_order = rhs.numRows();
        m_size = m_order;
        delete [] ptr_to_data;
        ptr_to_data = new T[m_size];

        for(int i = m_order-1; i >= 0; i--)
        {
            for(int j = m_order-1; j >= 0; j--)
            {
                if(i != j)
                {
                    if(rhs(i,j) != 0)
                        throw Incompatible_Matrix_Err();
                }
                else
                    *(ptr_to_data + j) = rhs(i,j);
            }
        }
    }
    else if(rhs_ptd == NULL)
    {
        m_order = 0;
        m_size = 0;
        delete [] ptr_to_data;
        ptr_to_data = NULL;
    }
    return *this;
}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator=(const DiagonalMatrix<T>& rhs)
{
    if(ptr_to_data != rhs.ptr_to_data)
    {
        m_order = rhs.m_order;
        m_size = m_order;
        if(ptr_to_data != NULL)
            delete [] ptr_to_data;
        ptr_to_data = new T[m_size];
        copy(rhs);
    }
    return *this;
}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator+=(const Base_Matrix<T>& rhs)
{
    if(rhs.numRows() != m_order || rhs.numCols() != m_order)
    {
        throw Incompatible_Matrix_Err();
    }    
    
    for(int i = m_order-1; i >= 0; i--)
    {
        for(int j = m_order-1; j >= 0; j--)
        {
            if(i != j)
            {
                if(rhs(i,j) != 0)
                    throw Incompatible_Matrix_Err();
            }
            else
                *(ptr_to_data + j) += rhs(i,j);
        }
    }
    
    return *this;  
}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator+=(const DiagonalMatrix<T>& rhs)
{
    if(rhs.m_order != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    T* p = ptr_to_data + m_size;
    T* q = rhs.ptr_to_data + m_size;
    while(p > ptr_to_data) *--p += *--q;
    
    return *this;
}

template <class T>
DiagonalMatrix<T>  DiagonalMatrix<T>::operator-() const
{
    DiagonalMatrix<T> neg(m_order);
    
    T* s = neg.ptr_to_data + m_size;
    T* p = ptr_to_data + m_size;
    while(s > neg.ptr_to_data) *--s = *--p * -1;
    
    return neg;
}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator-=(const Base_Matrix<T>& rhs)
{
    if(rhs.numRows() != m_order || rhs.numCols() != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    for(int i = m_order-1; i >= 0; i--)
    {
        for(int j = m_order-1; j >= 0; j--)
        {
            if(i != j)
            {
                if(rhs(i,j) != 0)
                    throw Incompatible_Matrix_Err();
            }
            else
                *(ptr_to_data + j) -= rhs(i,j);
        }
    }
    
    return *this;  
}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator-=(const DiagonalMatrix<T>& rhs)
{
    if(rhs.m_order != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    T* p = ptr_to_data + m_size;
    T* q = rhs.ptr_to_data + m_size;
    while(p > ptr_to_data) *--p -= *--q;
    
    return *this;
}

template <class T>
DiagonalMatrix<T>  DiagonalMatrix<T>::operator*(const T scalar) const
{
    DiagonalMatrix<T> scaled(m_order);
    
    T* s = scaled.ptr_to_data + m_size;
    T* p = ptr_to_data + m_size;
    while(s > scaled.ptr_to_data) *--s = *--p * scalar;
    
    return scaled;
}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator*=(const T scalar)
{
    T* p = ptr_to_data + m_size;
    while(p > ptr_to_data) *--p *= scalar;
    
    return *this;
}

template <class T>
Vector<T> DiagonalMatrix<T>::operator*(const Vector<T>& rhs) const
{
    unsigned int size = rhs.getSize();
    
    if(size != m_order)
    {
        throw Incompatible_Vector_Err();
    }
    
    Vector<T> b(m_order);
   
    for(int i = m_order-1; i >= 0; i--)
    {
        b[i] = *(ptr_to_data + i) * rhs[i];
    }
    
    return b;
}

template <class T>
void DiagonalMatrix<T>::SetAll(T value)
{
    for(unsigned int i = 0; i < m_size; i++)
    {
        ptr_to_data[i] = value;
    }
}

template <class T>
void DiagonalMatrix<T>::Zero()
{
    for(unsigned int i = 0; i < m_size; i++)
    {
        ptr_to_data[i] = 0;
    }
}

template <class T>
void DiagonalMatrix<T>::Resize(const unsigned int order)
{
    m_order = order;
    m_size = order;
    if(ptr_to_data != NULL)
        delete [] ptr_to_data;
    ptr_to_data = new T[m_size];
    
    Zero();
}

//Copy Matrix Elements (Private)
template <class T>
void DiagonalMatrix<T>::copy(const DiagonalMatrix<T>& src)
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

