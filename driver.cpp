////////////////////////////////////////////////////////////////
///  driver.cpp
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
///  Driver file for testing the Matrix class and Gaussian
///  Solver class implementations.
////////////////////////////////////////////////////////////////

#define google_test_enabled true
#include "test_vector.cpp"
#include "test_symmetricalMatrix.cpp"
#include "test_matrix.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstring>
#include <string>

#if google_test_enabled
  #include <gtest/gtest.h>
#endif

#include "Matrix.h"
#include "SymmetricalMatrix.h"
#include "Vector.h"
#include "SOE_Solver.h"
#include "IM_Solver.h"
#include "Central_Diff_Oh2.h"
using namespace std;

/////////////////////////////////////////////////
// Definitions for PDE boundaries and solution //
/////////////////////////////////////////////////
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

const Parameters<double> p = {0,PI,0,PI};

/////////////////////////////////////////////////
//           End of PDE definitions            //
/////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
// List of run commands (See ReadMe for more details)         //
//                                                            //
//  ./driver <mesh_size> soe  <Method>                        //
//  ./driver <mesh_size> it   <Method> <TOL> <Limit>          //
//  ./driver <mesh_size> spec <TOL> <Limit>                   //
////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
     if(strcmp(argv[1],"--test") == 0)
    {
      /*
       * If the '--test' flag is used then we only want to run the unit tests. So, here we go.
       * gtest wasn't wanting to work correctly on the CS machines... Taking out for now.
       */
       #if google_test_enabled
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
       #else
        cout<<"\nUnfortunately the gtest framework wasn't working right on the schools CS machines. So, it has been removed for now. :("<<endl;
        cout<<"If, however, you know it installed then set the google_test_enabled value to 'true' and switch the CXXFLAGS in the makefile!\n\n"<<endl;
        return 0;
       #endif      
    }
    
    if(argc < 3)
    {
        cout << "Run information missing. Check parameters listed in ReadMe.txt." << endl;
        exit(1);
    }
    
    //General-use variables
    unsigned int N = atoi(argv[1]);
    
    stringstream filename; 
    
    Matrix<double> mat;
    SymmetricalMatrix<double> sym;
    Vector<double> b;
    Vector<double> x_axis;
    Vector<double> y_axis;
    Vector<double> ans;
    //Vector<double> sol;   //Unused now.
    
    //Setup general variables
    Central_Diff_Oh2 CD;
    CD.generate_Vector(b,N,p,x_l,x_u,y_l,y_u);
    CD.generate_Axes(x_axis,y_axis,N,p);
    //CD.generate_Solution(sol,N,p,solution); //Unused now.
    
    char method[10];
    strcpy(method, argv[2]);
    
    filename << "Run_Folder/" << "N" << N << "_" << method;
    
    //Get start time
    time_t start = time(0);
    
    //Run method
    if(!strcmp(method,"soe"))
    {
        if(argc != 4)
        {
            cout << "SOE: Incorrect number of parameters given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        int type = atoi(argv[3]);
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
        if(argc != 6)
        {
            cout << "IT: Incorrect number of parameters given. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        IterationType IT = static_cast<IterationType>(atoi(argv[3]));
        double TOL = atof(argv[4]);
        int limit = atoi(argv[5]);
        
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
        
        CD.generate_Matrix(mat,N);
        ans = IM_Solver()(mat,b,XO,TOL,limit,IT);

    }
    else if(!strcmp(method,"spec"))
    {
        if(argc != 5)
        {
            cout << "SPEC: Incorrect number of parameters for special method run. Check parameters listed in Readme.txt." << endl;
            exit(1);
        }
        
        double TOL = atof(argv[3]);
        int limit = atoi(argv[4]);
        
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
        for(unsigned int i = 0; i < y_axis.getSize(); i++)
        {
            for(unsigned int j = 0; j < x_axis.getSize(); j++)
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

