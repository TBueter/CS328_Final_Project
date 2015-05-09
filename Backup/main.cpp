#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include "Matrix.h"
#include "Vector.h"
#include "SymmetricalMatrix.h"
#include "MeshMatrix.h"
#include "SOE_Solver.h"
#include "IM_Solver.h"
#include "PDE_Problem.h"
using namespace std;

#define PI 3.14159265359

double x_l(double x, double y)
{
    return sin(y);
}

double x_u(double x, double y)
{
    return 0;
}

double y_l(double x, double y)
{
    return sin(x);
}

double y_u(double x, double y)
{
    return 0;
}

double solution(double x, double y)
{
    return (1/sinh(PI))*(sin(x)*sinh(PI-y)+sin(y)*sinh(PI-x));   
}

template <class T>
T L2_norm(const Vector<T>& x)
{
    T norm = 0;
    for(int i = 0, size = x.getSize(); i < size; i++)
    {
        norm += x[i]*x[i];
    }
    norm = sqrt(norm);
    return norm;
}

template <class T>
void Modified_GS_Iter(const Vector<T>& b,
                      Vector<T>& XO,
                      const T TOL,
                      const unsigned int Limit,
                      Solution<T>& sol)
{
    unsigned int k = 1, n = b.getSize();
    unsigned int N = sqrt(n)+1;
    cout << N << endl;
    Vector<T> x(n);
    sol.init_vec = XO;
    sol.tol = TOL;
    
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
            sol.sol_vec = x;
            sol.num_iter = k;
            sol.sol_found = true;
            return;
        }
        k++;
        XO = x;
    }
    sol.num_iter = Limit;
}

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
	MeshMatrix<double> M;
    
	Matrix<double> A;
	SymmetricalMatrix<double> S;
	Vector<double> b;
	//Vector<double> ans;
	Vector<double> XO((N-1)*(N-1));
	Parameters<double> p = {0,PI,0,PI};
	
	Vector<double> sol((N-1)*(N-1));
	for(int i = 1; i < N; i++)
	{
	    for(int j = 1; j < N; j++)
	    {
	        sol[(N-1)*(i-1)+(j-1)] = solution(p.xlb+(p.xub-p.xlb)/N*j,p.ylb+(p.yub-p.ylb)/N*i);
	    }
	}


	PDE_Problem()(M,b,N,p,x_l,x_u,y_l,y_u);
	
	Solution<double> ans;
	XO = 1;
	Modified_GS_Iter(b,XO,0.001,100000,ans);
	
	//cout << ans << endl;

	//ans = SOE_Solver()(S,b);
	
	//XO = 1;
	//Solution<double> ans = IM_Solver()(M,b,XO,0.001,10000,JACOBI);

    cout << ans << endl;
	//cout << ans.sol_vec << endl;
	
    return 0;
}
