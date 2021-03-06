////////////////////////////////////////////////////////////////
///  IncompatibleVectorErr.h
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
///  Exception handling class for errors when performing 
///  operations on vectors with different sizes.
////////////////////////////////////////////////////////////////

#ifndef  INCOMPATIBLEVECTORERR_H
#define  INCOMPATIBLEVECTORERR_H

////////////////////////////////////////////////////////////////
///  Class: Incompatible_Vector_Err
////////////////////////////////////////////////////////////////
class Incompatible_Vector_Err
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Incompatible_Vector_Err
        ///  Brief:  Constructor for class. This is just used for 
        ///          handling this type of error in the Vector class.
        ////////////////////////////////////////////////////////////////
        Incompatible_Vector_Err() {}

};

#endif //INCOMPATIBLEVECTORERR_H
