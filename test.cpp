#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include "Matrix.h"
#include "SymmetricalMatrix.h"
#include "Vector.h"
#include "SOE_Solver.h"
#include "IM_Solver.h"
#include "Central_Diff_Oh2.h"
using namespace std;

#define PI 3.14159265358979323846

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


// ./a.out <runID> <mesh_size> soe <Method>
// ./a.out <runID> <mesh_size> it <Method> <Matrix> <TOL> <Limit>
// ./a.out <runID> <mesh_size> spec <TOL> <Limit>
int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        cout << "Run information missing. Check parameters listed in ReadMe.txt." << endl;
        exit(1);
    }
    
    //General-use variables
    unsigned int runID = atoi(argv[1]);
    unsigned int N = atoi(argv[2]);
    
    stringstream filename; 
    
    Matrix<double> mat;
    SymmetricalMatrix<double> sym;
    Vector<double> b;
    Vector<double> x_axis;
    Vector<double> y_axis;
    Vector<double> ans;
    Vector<double> sol;
    Parameters<double> p = {0,PI,0,PI};
    
    //Setup general variables
    Central_Diff_Oh2 CD;
    CD.generate_Vector(b,N,p,x_l,x_u,y_l,y_u);
    CD.generate_Axes(x_axis,y_axis,N,p);
    CD.generate_Solution(sol,N,p,solution);
    
    char method[5];
    strcpy(method, argv[3]);
    
    filename << "Run_Folder/run" << runID << "_N" << N << "_" << method;
    
    //Get start time
    time_t start = time(0);
    
    //Run method
    if(!strcmp(method,"soe"))
    {
        if(argc != 5)
        {
            cout << "SOE: Incorrect number of parameters given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        int type = atoi(argv[4]);
        if(type == STANDARD)
        {
            filename << "_std";
            CD.generate_Matrix(mat,N);
            ans = SOE_Solver()(mat,b);
        }
        else if(type == SYMMETRICAL)
        {
            filename << "_sym";
            CD.generate_Matrix(sym,N);
            ans = SOE_Solver()(sym,b);
        }
        else
        {
            cout << "SOE: Unusable matrix type given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
    }
    else if(!strcmp(method,"it"))
    {
        if(argc != 8)
        {
            cout << "IT: Incorrect number of parameters given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        IterationType IT = static_cast<IterationType>(atoi(argv[4]));
        int mat_type = atoi(argv[5]);
        double TOL = atof(argv[6]);
        int limit = atoi(argv[7]);
        
        Vector<double> XO((N-1)*(N-1));
        XO = 1;
        
        if(IT == JACOBI)
        {
            filename << "_jacobi";
        }
        else if(IT == GAUSS_SEIDEL)
        {
            filename << "_gauss_seidel";
        }
        else
        {
            cout << "IT: Unusable iterative method type given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        if(mat_type == STANDARD)
        {
            filename << "_std";
            CD.generate_Matrix(mat,N);
            ans = IM_Solver()(mat,b,XO,TOL,limit,IT);
        }
        else if(mat_type == SYMMETRICAL)
        {
            filename << "_sym";
            CD.generate_Matrix(sym,N);
            ans = IM_Solver()(sym,b,XO,TOL,limit,IT);
        }
        else
        {
            cout << "IT: Unusable matrix type given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
    }
    else if(!strcmp(method,"spec"))
    {
        if(argc != 6)
        {
            cout << "SPEC: Incorrect number of parameters for special method run. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        double TOL = atof(argv[4]);
        int limit = atoi(argv[5]);
        
        Vector<double> XO((N-1)*(N-1));
        XO = 1;

        ans = CD.Special_Solver(b,XO,TOL,limit);        
        
    }
    else
    {
        cout << "ERR: Undefined method given. Check parameters listed in Readme.txt." << endl;
        exit(1);
    }
    
    //Get finish time
    time_t finish = difftime(time(0), start);
    
    filename << ".txt";
    string tmp = filename.str();
    
    ofstream run_file;
    run_file.open(tmp.c_str(), ios::out | ios::trunc);
    
    if(ans.getSize() != 0)
    {
         for(int i = 0; i < y_axis.getSize(); i++)
        {
            for(int j = 0; j < x_axis.getSize(); j++)
            {
                run_file << x_axis[j]<< ", " << y_axis[i] << ", " << ans[(N-1)*i+j] << endl; 
            }
        }
    }
    else { run_file << "No solution found." << endl; }
    
    run_file.close();
    
    cout << "Finished: " << floor(finish/60) << " min " << finish%60 << " sec" << endl;
    return 0;
}

