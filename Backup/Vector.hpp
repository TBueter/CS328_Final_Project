////////////////////////////////////////////////////////////////
///  Vector.hpp
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
///  Templated class definition for a mathematical vector data
///  representation. This class is based on the array class
///  described in the Scientific and Engineering C++ book for 
///  this course.
////////////////////////////////////////////////////////////////


//Create vector with n elements
template <class T>
Vector<T>::Vector(unsigned int n)
{
    m_size = n;
    ptr_to_data = new T[n];
	for(unsigned int i = 0; i < m_size; i++)
	{
		ptr_to_data[i] = 0;
	}
}

//Copy vector
template <class T>
Vector<T>::Vector(const Vector<T>& src)
{
    m_size = src.m_size;
	ptr_to_data = new T[m_size];
	copy(src);
}

template <class T>
Vector<T>::Vector(initializer_list<T> list)
{
	m_size = list.size();
	ptr_to_data = new T[m_size];

	unsigned int k = 0;
	for(auto i : list)
	{
		ptr_to_data[k++] = i;
	}
}

//Deconstructor
template <class T>
Vector<T>::~Vector()
{
    if(ptr_to_data != NULL)
	{
		delete [] ptr_to_data;
	}
}

//Accessor
template <class T>
T Vector<T>::operator[](const unsigned int i) const
{
	if(i >= m_size)
	{
	    throw Out_Of_Range_Err(i);
	}
	return ptr_to_data[i];
}

//Mutator
template <class T>
T& Vector<T>::operator[](const unsigned int i)
{
    if(i >= m_size)
    {
        throw Out_Of_Range_Err(i);
    }
    return ptr_to_data[i];
}

//Vector Assignment
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& src)
{
	if(ptr_to_data != src.ptr_to_data)
	{
		setSize(src.m_size);
		copy(src);
	}
	return *this;
}

//Scalar Assignment
template <class T>
Vector<T>& Vector<T>::operator=(const T scalar)
{
	if(ptr_to_data != NULL)
	{
		T* p = ptr_to_data + m_size;
		while(p > ptr_to_data) *--p = scalar;
	}
	return *this;
}

//Vector Addition
template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& rhs) const
{
	if(m_size != rhs.m_size)
	{
		throw Incompatible_Vector_Err();
	}
	
	Vector<T> sum(m_size);
	T* s = sum.ptr_to_data + m_size;
	T* p = ptr_to_data + m_size;
	T* q = rhs.ptr_to_data + m_size;
	while(s > sum.ptr_to_data) *--s = *--p + *--q;
	
	return sum;
}

//Vector Negative
template <class T>
Vector<T> Vector<T>::operator-() const
{
	return ((*this) * -1);
}

//Vector Subtraction
template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& src) const
{
	return ((*this) + (-src));
}

//Dot Product
template <class T>
T Vector<T>::operator*(const Vector<T>& rhs) const
{
	if(m_size != rhs.m_size)
	{
		throw Incompatible_Vector_Err();
	}
	
	T product = 0;
	T* p = ptr_to_data + m_size;
	T* q = rhs.ptr_to_data + m_size;
	while(p > ptr_to_data) product += ((*--p) * (*--q));
	
	return product;
}

//Scalar Multiplication Right-hand side (Improper)
template <class T>
Vector<T> Vector<T>::operator*(const T scalar) const
{

	Vector<T> scaled(m_size);
	T* s = scaled.ptr_to_data + m_size;
	T* p = ptr_to_data + m_size;
	while(s > scaled.ptr_to_data) *--s = *--p * scalar;
	
	return scaled;
}

//Get Size
template <class T>
unsigned int Vector<T>::getSize() const
{
	return m_size;
}

template <class T>
void Vector<T>::Swap(const unsigned int i, const unsigned int j)
{
	if(i >= m_size || j >= m_size)
		return; //Throw invalid Vector operation
		
	if(i == j)
		return;
		
	T temp = *(ptr_to_data + i);
	*(ptr_to_data + i) = *(ptr_to_data + j);
	*(ptr_to_data + j) = temp;
}

//Set Size
template <class T>
void Vector<T>::setSize(const unsigned int n)
{
	if(n == 0)
	{
		delete [] ptr_to_data;
		ptr_to_data = NULL;
		m_size = 0;
	}
	else if( n != m_size)
	{
		delete [] ptr_to_data;
		m_size = n;
		ptr_to_data = new T[n];
		for(unsigned int i = 0; i < m_size; i++)
		{
			ptr_to_data[i] = 0;
		}
	}
}

//Copy Vector Elements (Private)
template <class T>
void Vector<T>::copy(const Vector<T>& src)
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
