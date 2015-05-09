////////////////////////////////////////////////////////////////
///  MeshMatrix.hpp
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
///  Templated class definition for a mathematical symmetrical
///  matrix data representation. This class is based 
///  on the array class described in the Scientific and 
///  Engineering C++ book for this course.
////////////////////////////////////////////////////////////////

//////////// Constructs ///////////
template <class T>
MeshMatrix<T>::MeshMatrix()
{
    m_mesh_deg = 0;
    m_order = 0;
}

template <class T>
MeshMatrix<T>::MeshMatrix(const unsigned int mesh_deg)
{
    m_mesh_deg = mesh_deg;
    m_order = (mesh_deg-1)*(mesh_deg-1);
}

template <class T>
MeshMatrix<T>::MeshMatrix(const MeshMatrix<T>& src)
{
    m_mesh_deg = src.m_mesh_deg;
    m_order = (src.mesh_deg-1)*(src.mesh_deg-1);
}

//////// Virtual functions ////////
template <class T>
T MeshMatrix<T>::operator()(const unsigned int row, const unsigned int col) const
{
    if(row >= m_order || col >= m_order)
    {
        throw Out_Of_Range_Err(m_order*row+col);
    }
    
    unsigned int x;
    if(row > col)
        x = row-col;
    else
        x = col-row;
        
    if(x == 0)
    {
        return 1;
    }
    else if((x == m_mesh_deg-1) ||
            (x == 1 && (row > col ? (row%(m_mesh_deg-1)!=0) 
                                  : (col%(m_mesh_deg-1)!=0))))
    {
        return -0.25;
    }
    else
    {
        return 0;
    }
}

template <class T>
T& MeshMatrix<T>::operator()(const unsigned int row, const unsigned int col)
{
    //Error
}

template <class T>
Matrix<T> MeshMatrix<T>::operator*(const Base_Matrix<T>& rhs) const
{
    if(rhs.numRows() != m_order)
    {
        throw Incompatible_Matrix_Err();
    }
    
    unsigned int cols = rhs.numCols();
    
    Matrix<T> C(m_order,cols);
    
    T sum;
    for(int i = m_order-1; i >= 0; i--)
    {
        for(int j = cols-1; j >= 0; j--)
        {
            sum = rhs(i,j);
            if(i > 0 && (i%(m_mesh_deg-1)!=0))
                sum += -0.25*rhs(i-1,j);
            if(i < m_order-1 && ((i+1)%(m_mesh_deg-1)!=0))
                sum += -0.25*rhs(i+1,j);
            if(i >= (m_mesh_deg-1))
                sum += -0.25*rhs(i-m_mesh_deg+1,j);
            if(i <= (m_order - m_mesh_deg))
                sum += -0.25*rhs(i+m_mesh_deg-1,j);
            C(i,j) = sum;
        }
    }
    
    return C;
}

template <class T>
Matrix<T> MeshMatrix<T>::operator+(const Base_Matrix<T>& rhs) const
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
            sum(i,j) = (*this).operator()(i,j) + rhs(i,j);
        }
    }
    
    return sum;
}

template <class T>
Matrix<T> MeshMatrix<T>::operator-(const Base_Matrix<T>& rhs) const
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
            diff(i,j) = (*this).operator()(i,j) - rhs(i,j);
        }
    }
    
    return diff;
}

template <class T>
void MeshMatrix<T>::Resize(const unsigned int rows, const unsigned int cols)
{
    m_order = rows;
    m_mesh_deg = sqrt(rows)+1;
}


///////// Member functions ////////

template <class T>
Vector<T> MeshMatrix<T>::operator*(const Vector<T>& rhs) const
{
    unsigned int size = rhs.getSize();
    
    if(size != m_order)
    {
        throw Incompatible_Vector_Err();
    }
    
    Vector<T> b(m_order);
    
    T sum;
    for(int i = m_order-1; i >= 0; i--)
    {
        sum = 0;
        if(i > 0 && (i%(m_mesh_deg-1)!=0))
            sum += -0.25*rhs[i-1];
        if(i < m_order-1 && ((i+1)%(m_mesh_deg-1)!=0))
            sum += -0.25*rhs[i+1];
        if(i >= (m_mesh_deg-1))
            sum += -0.25*rhs[i-m_mesh_deg+1];
        if(i <= (m_order - m_mesh_deg))
            sum += -0.25*rhs[i+m_mesh_deg-1];
        b[i] = sum;
    }
    
    return b;
}
