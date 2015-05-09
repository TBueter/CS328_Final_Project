       
template <class T, typename F>
void PDE_Problem::operator()(Base_Matrix<T>& A, 
                             Vector<T>& b,
                             const unsigned int N, 
                             const Parameters<T> p,
                             const F xlf,
                             const F xuf,
                             const F ylf,
                             const F yuf)
{
    unsigned int size = (N-1)*(N-1);
    
    //Set up Matrix
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
        case MESH:
            break;
        default:
            cout << "ERROR: Matrix is not compatable." << endl;
            break;
    }
    
    //Set up Vector
    b.setSize(size);
    T sum, j, k;
    T x_step = (p.xub-p.xlb)/N;
    T y_step = (p.yub-p.ylb)/N;
    for(int i = 0; i < size; i++)
    {
        sum = 0;
        j = i%(N-1) + 1;
        k = floor(i/(N-1))+1;
        
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
