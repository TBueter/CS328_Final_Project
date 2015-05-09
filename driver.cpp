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
///  Driver file for testing the Matrrix class and Gaussian
///  Solver class implementations.
////////////////////////////////////////////////////////////////

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
#include "TridiagonalMatrix.h"
#include "DiagonalMatrix.h"
#include "SymmetricalMatrix.h"
#include "UpperTriangularMatrix.h"
#include "LowerTriangularMatrix.h"
#include "SOE_Solver.h"
using namespace std;

int main(int argc, char *argv[])
{
    unsigned int i, j, size;
    double input;
    ifstream inFile;
    
    //Check that a parameter was given for file name
    if(!(argc > 1))
    {
        cerr << "Give valid input file. Exiting..." << endl;
        exit(1);
    }
    
     // Open input file
    inFile.open(argv[1], ios::in);
    if(!inFile.is_open())
    {
        cerr << "Can't open input file " << argv[1] << endl;
        exit(1);
    }

    
    //Get the first line which give the matrix and vector dimension.
    string s; istringstream iss;
    while(getline(inFile, s) && s.empty());
    
    iss.str(s);
    iss >> size;
    iss.clear();

    Matrix<double> A1(size,size);
    i = 0;
    while(getline(inFile, s) && !s.empty())
    {
        j = 0;
        iss.str(s);
        while(j < size && (iss >> input))
        {
            A1(i,j) = input;
            j++;
        }
        i++;
        iss.clear();
    }
    
    Vector<double> b1(size);
    while(getline(inFile, s) && !s.empty())
    {
        j = 0;
        iss.str(s);
        while(j < size && (iss >> input))
        {
            b1[j] = input;
            j++;
        }
        iss.clear();
    }
    
    ///////////////////////////////////////
    while(getline(inFile, s) && s.empty());
    
    iss.str(s);
    iss >> size;
    iss.clear();

    Matrix<double> A2(size,size);
    i = 0;
    while(getline(inFile, s) && !s.empty())
    {
        j = 0;
        iss.str(s);
        while(j < size && (iss >> input))
        {
            A2(i,j) = input;
            j++;
        }
        i++;
        iss.clear();
    }
    
    Vector<double> b2(size);
    while(getline(inFile, s) && !s.empty())
    {
        j = 0;
        iss.str(s);
        while(j < size && (iss >> input))
        {
            b2[j] = input;
            j++;
        }
        iss.clear();
    }
    
    inFile.close();
    
    // These test the implementations of the Vector and Jacobi Method
    // classes as described in the homework description. Note that there
    // are some extra tests included, along with others that are 
    // commented-out.
    
    cout << endl << "/************** MATRIX CLASS TESTS **************\\" << endl << endl;
    
    /******************* TEST #1 *******************/
    
    cout << "Test #1:  Demonstration of the default constructor." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test1_S;
        TridiagonalMatrix<int> Test1_T;
        DiagonalMatrix<int>    Test1_D;
    
        cout << "Test 1 S Matrix:\n" << Test1_S << endl;
        cout << "Test 1 T Matrix:\n" << Test1_T << endl;
        cout << "Test 1 D Matrix:\n" << Test1_D << endl;
    }
    
    cout << endl << endl;
    
    /******************* TEST #2 *******************/
            
    cout << "Test #2:  Demonstration of the primary constructor." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test2_S(1);
        TridiagonalMatrix<int> Test2_T(2);
        DiagonalMatrix<int>    Test2_D(3);
    
        cout << "Test 2 S Matrix:\n" << Test2_S << endl;
        cout << "Test 2 T Matrix:\n" << Test2_T << endl;
        cout << "Test 2 D Matrix:\n" << Test2_D << endl;
    }
    
    cout << endl << endl;
    
    /******************* TEST #3 *******************/
                
    cout << "Test #3:  Demonstration of the alternate constructor." << endl << endl;
 
    if(true)
    {
        SymmetricalMatrix<int> Test3_S(3,1);
        TridiagonalMatrix<int> Test3_T(4,2);
        DiagonalMatrix<int>    Test3_D(5,3);
    
        cout << "Test 3 S Matrix:\n" << Test3_S << endl;
        cout << "Test 3 T Matrix:\n" << Test3_T << endl;
        cout << "Test 3 D Matrix:\n" << Test3_D << endl;
    }
    
    cout << endl << endl;

    
    /******************* TEST #4 *******************/
                
    cout << "Test #4:  Demonstration of the copy constructor." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test_S(3,1);
        TridiagonalMatrix<int> Test_T(4,2);
        DiagonalMatrix<int>    Test_D(5,3);
        
        SymmetricalMatrix<int> Test4_S(Test_S);
        TridiagonalMatrix<int> Test4_T(Test_T);
        DiagonalMatrix<int>    Test4_D(Test_D);
        
        cout << "Test 4 S Matrix:\n" << Test4_S << endl;
        cout << "Test 4 T Matrix:\n" << Test4_T << endl;
        cout << "Test 4 D Matrix:\n" << Test4_D << endl;
    }
    
    cout << endl << endl;
    
    
    /******************* TEST #5 *******************/
                
    cout << "Test #5:  Demonstration of the initialization constructor." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test5_S = {{6,15,55},{51,225},{979}};
        TridiagonalMatrix<int> Test5_T = {{1,2},{3,4,5},{6,7}};
        DiagonalMatrix<int>    Test5_D = {{3},{7},{-22}};
        
        cout << "Test 5 S Matrix:\n" << Test5_S << endl;
        cout << "Test 5 T Matrix:\n" << Test5_T << endl;
        cout << "Test 5 D Matrix:\n" << Test5_D << endl;
    }
    
    cout << endl << endl;


    /******************* TEST #6 *******************/
                    
    cout << "Test #6:  Demonstration of the Accessor and Mutator operators." << endl << endl;
    
    if(true)
    {
        SymmetricalMatrix<int> Test6_S = {{6,15,55},{51,225},{979}};
        TridiagonalMatrix<int> Test6_T = {{1,2},{3,4,5},{6,7}};
        DiagonalMatrix<int>    Test6_D = {{3},{7},{-22}};
        
        Test6_S(0,1) = Test6_T(0,1);
        Test6_S(1,2) = Test6_T(1,2);
        
        Test6_T(1,0) = Test6_D(0,0);
        Test6_T(2,1) = Test6_D(2,2);
        
        Test6_D(0,0) = Test6_S(0,0);
        Test6_D(2,2) = Test6_S(2,2);  
        
        cout << "Test 6 S Matrix:\n" << Test6_S << endl;
        cout << "Test 6 T Matrix:\n" << Test6_T << endl;
        cout << "Test 6 D Matrix:\n" << Test6_D << endl;
        
        try
        {
            Test6_T(0,2) = 1;
        }
        catch(Out_Of_Range_Err e)
        {
            cout << "T: You can't change elements outside the tridiagonal!" << endl;
        }
        
        try
        {
            Test6_D(0,1) = 1;
        }
        catch(Out_Of_Range_Err e)
        {
            cout << "D: You can't change elements outside the diagonal!" << endl;
        }
    }
    
    
    /******************* TEST #7 *******************/
                        
    cout << "Test #7:  Demonstration of the assignment operators." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test_S = {{6,0,0},{51,0},{979}}; 
        TridiagonalMatrix<int> Test_T = {{1,2},{2,4,5},{5,7}};
        DiagonalMatrix<int>    Test_D = {{3},{7},{-22}};
        
        SymmetricalMatrix<int> Test7_S;
        TridiagonalMatrix<int> Test7_T;
        DiagonalMatrix<int>    Test7_D;
        
        Test7_S = Test_T;
        Test7_T = Test_D;
        Test7_D = Test_S;
        
        cout << "Test 7 S Matrix:\n" << Test7_S << endl;
        cout << "Test 7 T Matrix:\n" << Test7_T << endl;
        cout << "Test 7 D Matrix:\n" << Test7_D << endl;      
    }
    
    cout << endl << endl;
    

    /******************* TEST #8 *******************/
                        
    cout << "Test #8:  Demonstration of the addition operators." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test_S = {{6,0,0},{51,0},{979}}; 
        TridiagonalMatrix<int> Test_T = {{1,2},{2,4,5},{5,7}};
        DiagonalMatrix<int>    Test_D = {{3},{7},{-22}};
        
        SymmetricalMatrix<int> Test8_S = {{6,15,55},{51,225},{979}};
        TridiagonalMatrix<int> Test8_T = {{1,2},{3,4,5},{6,7}};
        DiagonalMatrix<int>    Test8_D = {{3},{7},{-22}};
        
        cout << "Test 8 S+T Matrix:\n" << Test8_S << "+\n" 
                                       << Test_T  << "=\n" 
                                       << Test8_S+Test_T << endl;
        cout << "Test 8 T+D Matrix:\n" << Test8_T << "+\n" 
                                       << Test_D  << "=\n" 
                                       << Test8_T+Test_D << endl;
        cout << "Test 8 D+S Matrix:\n" << Test8_D << "+\n" 
                                       << Test_S  << "=\n" 
                                       << Test8_D+Test_S << endl;
                                       
        Test8_S += Test_T;
        Test8_T += Test_D;
        Test8_D += Test_S;
        
        cout << "Test 8 S+=T Matrix:\n" << Test8_S << endl;
        cout << "Test 8 T+=D Matrix:\n" << Test8_T << endl;
        cout << "Test 8 D+=S Matrix:\n" << Test8_D << endl;
    }
    
    cout << endl << endl;
    
    
    /******************* TEST #9 *******************/
                        
    cout << "Test #9:  Demonstration of the negative and subtraction operators." << endl << endl;

    if(true)
    {
        SymmetricalMatrix<int> Test_S = {{6,0,0},{51,0},{979}}; 
        TridiagonalMatrix<int> Test_T = {{1,2},{2,4,5},{5,7}};
        DiagonalMatrix<int>    Test_D = {{3},{7},{-22}};
        
        SymmetricalMatrix<int> Test9_S = {{6,15,55},{51,225},{979}};
        TridiagonalMatrix<int> Test9_T = {{1,2},{3,4,5},{6,7}};
        DiagonalMatrix<int>    Test9_D = {{3},{7},{-22}};
        
        cout << "Test 9 S-T Matrix:\n" << Test9_S << "-\n" 
                                       << Test_T  << "=\n" 
                                       << Test9_S-Test_T << endl;
        cout << "Test 9 T-D Matrix:\n" << Test9_T << "-\n" 
                                       << Test_D  << "=\n" 
                                       << Test9_T-Test_D << endl;
        cout << "Test 9 D-S Matrix:\n" << Test9_D << "-\n" 
                                       << Test_S  << "=\n" 
                                       << Test9_D-Test_S << endl;
                                       
        Test9_S -= Test_T;
        Test9_T -= Test_D;
        Test9_D -= Test_S;
        
        cout << "Test 9 S-=T Matrix:\n" << Test9_S << endl;
        cout << "Test 9 T-=D Matrix:\n" << Test9_T << endl;
        cout << "Test 9 D-=S Matrix:\n" << Test9_D << endl;
    }
    
    cout << endl << endl;


    /******************* TEST #10 *******************/
                        
    cout << "Test #10:  Demonstration of the multiplication operators." << endl << endl;
    
    if(true)
    {
        SymmetricalMatrix<int> Test_S = {{6,0,0},{51,0},{979}}; 
        TridiagonalMatrix<int> Test_T = {{1,2},{2,4,5},{5,7}};
        DiagonalMatrix<int>    Test_D = {{3},{7},{-22}};        
        Vector<int>            Test_V = {1,2,3};
        
        SymmetricalMatrix<int> Test10_S = {{6,15,55},{51,225},{979}};
        TridiagonalMatrix<int> Test10_T = {{1,2},{3,4,5},{6,7}};
        DiagonalMatrix<int>    Test10_D = {{3},{7},{-22}};

        cout << "Test 10 S*T Matrix:\n" << Test10_S*Test_T << endl;
        cout << "Test 10 T*D Matrix:\n" << Test10_T*Test_D << endl;
        cout << "Test 10 D*S Matrix:\n" << Test10_D*Test_S << endl;
        
        cout << "Test 10 S*V Vector:\n" << Test10_S*Test_V << endl;
        cout << "Test 10 T*V Vector:\n" << Test10_T*Test_V << endl;
        cout << "Test 10 D*V Vector:\n" << Test10_D*Test_V << endl;
        
        cout << "Test 10 2*S Matrix:\n" << 2*Test10_S << endl;
        cout << "Test 10 2*T Matrix:\n" << 2*Test10_T << endl;
        cout << "Test 10 2*D Matrix:\n" << 2*Test10_D << endl;
                                       
        Test10_S *= 2;
        Test10_T *= 2;
        Test10_D *= 2;
        
        cout << "Test 10 S*=2 Matrix:\n" << Test10_S << endl;
        cout << "Test 10 T*=2 Matrix:\n" << Test10_T << endl;
        cout << "Test 10 D*=2 Matrix:\n" << Test10_D << endl;
    }
    
    cout << endl << endl;
    

    cout << endl << "/*** SYSTEM OF EQUATIONS SOLVER CLASS TEST ***\\" << endl << endl;
    
    /******************* TEST *******************/
    
    cout << "Test:  Demonstrate the SOE Solver implementation using the Thomas Algorithm and Cholesky Decomposition methods, via the provided dataset." << endl << endl;
    
    TridiagonalMatrix<double> T;
    T = A1;
    cout << "Matrix  T:\n" <<  T << endl;
    cout << "Vector b1:\n" << b1 << endl;
    cout << "Thomas Algorithm Solution:\n" << SOE_Solver()(T,b1) << endl;
    
    SymmetricalMatrix<double> S;
    S = A2;
    cout << "Matrix  S:\n" <<  S << endl;
    cout << "Vector b2:\n" << b2 << endl;
    cout << "Cholesky Decomposition Solution:\n" << SOE_Solver()(S,b2) << endl;

    return 0;
}
