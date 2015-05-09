////////////////////////////////////////////////////////////////
///  Central_Diff_Oh2.hpp
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

template <class T>
void Central_Diff_Oh2::generate_Matrix(Base_Matrix<T>& A, const unsigned int N)
{
    unsigned int size = (N-1)*(N-1);

    A.Resize(size,size);
    switch(A.getType())
    {
        case STANDARD:
            for(int i = 0; i < size; i++)
            {
                A(i,i) = 1;
                if(i < size-1 && (i+1)%(N-1) != 0)
                {
                    A(i+1,i) = -0.25;
                    A(i,i+1) = -0.25;
                }
                if(i < size-(N-1))
                {
                    A(i+(N-1),i) = -0.25;
                    A(i,i+(N-1)) = -0.25;
                }
            }
            break;
        case SYMMETRICAL:
            for(int i = 0; i < size; i++)
            {
                A(i,i) = 1;
                if(i < size-1 && (i+1)%(N-1) != 0)
                {
                    A(i+1,i) = -0.25;
                }
                if(i < size-(N-1))
                {
                    A(i+(N-1),i) = -0.25;
                }
            }
            break;
        default:
            cout << "ERROR: Matrix is not compatable." << endl;
            break;
    }
}

template <class T, class T_function>
void Central_Diff_Oh2::generate_Vector(Vector<T>& b,
                                       const unsigned int N,
                                       const Parameters<T> p,
                                       const T_function xlf,
                                       const T_function xuf,
                                       const T_function ylf,
                                       const T_function yuf)
    {
    unsigned int size = (N-1)*(N-1);
    
    b.setSize(size);
    T sum, j, k;
    T x_step = (p.xub-p.xlb)/N;
    T y_step = (p.yub-p.ylb)/N;
    for(int i = 0; i < size; i++)
    {
        sum = 0;
        j = i%(N-1) + 1;
        k = floor(i/(N-1)) + 1;
        
        if(j-1 == 0)
        {
            sum += xlf(p.xlb, k*y_step+p.ylb);
        }
        else if(j+1 == N)
        {
            sum += xuf(p.xub, k*y_step+p.ylb);
        }
        
        if(k-1 == 0)
        {
            sum += ylf(j*x_step+p.xlb,p.ylb);
        }
        else if(k+1 == N)
        {
            sum += yuf(j*x_step+p.xlb,p.yub);
        }
        
        b[i] = 0.25*sum;
    }
}

template <class T>                 
void Central_Diff_Oh2::generate_Axes(Vector<T>& x_axis,
                                     Vector<T>& y_axis,
                                     const unsigned int N,
                                     const Parameters<T> p)
{
    x_axis.setSize(N-1);
    y_axis.setSize(N-1);
    
    T x_step = (p.xub-p.xlb)/N;
    T y_step = (p.yub-p.ylb)/N;
    
    for(int i = 0; i < N-1; i++)
    {
        x_axis[i] = p.xlb+x_step*(i+1);
        y_axis[i] = p.ylb+y_step*(i+1);
    }
    
}                   
                   
template <class T, class T_function>
void Central_Diff_Oh2::generate_Solution(Vector<T>& sol, 
                                         const unsigned int N, 
                                         const Parameters<T> p,
                                         const T_function f)
{
    sol.setSize((N-1)*(N-1));
    
    for(int i = 1; i < N; i++)
    {
        for(int j = 1; j < N; j++)
        {
            sol[(N-1)*(i-1)+(j-1)] = f(p.xlb+(p.xub-p.xlb)/N*j,p.ylb+(p.yub-p.ylb)/N*i);
        }
    }
}

template <class T>             
Vector<T> Central_Diff_Oh2::Special_Solver(const Vector<T>& b,
                                           Vector<T>& XO,
                                           const T TOL,
                                           const unsigned int Limit)
{
    unsigned int k = 1, n = b.getSize();
    unsigned int N = sqrt(n)+1;
    Vector<T> x(n);
    
    if(XO.getSize() != n)
        throw Incompatible_Vector_Err();
     
    while(k <= Limit)
    {
        for(unsigned int i = 0; i < n; i++)
        {
            T sum = 0;  
            if(i > 0 && (i%(N-1)!=0))
                sum -= -0.25*XO[i-1];
            if(i < n-1 && ((i+1)%(N-1)!=0))
                sum -= -0.25*x[i+1];
            if(i >= (N-1))
                sum -= -0.25*x[i-N+1];
            if(i <= (n - N))
                sum -= -0.25*XO[i+N-1];

            x[i] = (sum+b[i]);
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
T Central_Diff_Oh2::L2_norm(const Vector<T>& x)
{
    T norm = 0;
    for(int i = 0, size = x.getSize(); i < size; i++)
    {
        norm += x[i]*x[i];
    }
    norm = sqrt(norm);
    return norm;
}

