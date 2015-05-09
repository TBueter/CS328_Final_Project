////////////////////////////////////////////////////////////////
///  IncompatibleMatrixErr.h
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
///  Exception handling class for errors when performing 
///  operations on matrices with different sizes.
////////////////////////////////////////////////////////////////

#ifndef  INCOMPATIBLEMATRIXERR_H
#define  INCOMPATIBLEMATRIXERR_H

////////////////////////////////////////////////////////////////
///  Class: Incompatible_Matrix_Err
////////////////////////////////////////////////////////////////
class Incompatible_Matrix_Err
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Incompatible_Matrix_Err
        ///  Brief:  Constructor for class. This is just used for 
        ///          handling this type of error in the Matrix class.
        ////////////////////////////////////////////////////////////////
        Incompatible_Matrix_Err() {}

};

#endif //INCOMPATIBLEMATRIXERR_H
