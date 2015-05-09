////////////////////////////////////////////////////////////////
///  OutOfRangeErr.h
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
///  Exception handling class for out of range errors.
////////////////////////////////////////////////////////////////

#ifndef  OUTOFRANGEERR_H
#define  OUTOFRANGEERR_H

////////////////////////////////////////////////////////////////
///  Class: Out_Of_Range_Err
////////////////////////////////////////////////////////////////
class Out_Of_Range_Err
{
    public:
        
        ////////////////////////////////////////////////////////////////
        ///  Func:   Out_Of_Range_Err
        ///  Brief:  Constructor for class.
        ///  Pre:    None
        ///  Post:   Out-of-range index value set.
        ///  Param:  i - Value of the out-of-range index.
        ////////////////////////////////////////////////////////////////
        Out_Of_Range_Err(unsigned int i): m_index(i) {}
        
        ///////////////////////////////////////////////////////////////
        ///  Func:   badIndex
        ///  Brief:  Returns the value of the out-of-range index value.
        ///  Pre:    None
        ///  Post:   None
        ///  Return: Returns the value of the out-of-range index value.
        ////////////////////////////////////////////////////////////////
        int badIndex() {return m_index;}
        
    private:
        unsigned int m_index;    //Out-of-range index value
};

#endif //OUTOFRANGEERR_H
