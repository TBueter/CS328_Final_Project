###############################################################################
#  Makefile
###############################################################################

###############################################################################
#
#  Programmer :  Travis Bueter
#  Assignment :  An Abstract Matrix Class and Some Derivatives
#
#  Instructor :  Prof. Clayton Price
#  Grader     :  Dr. Nathan "Waffles" Eloe, a.k.a. C++ Guru
#                Ph.D., Computer Science
#                B.S., Computer Science
#                B.S., Physics
#                Judan, C++ Ninjutsu
#
#  Course     :  CS5201
#  Semester   :  Spring 2015
#
###############################################################################

###############################################################################
#  This makefile will build an executable for the assignment. Modified from a
#  generalized makefile created by Rob Wiehage.
###############################################################################

.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -std=c++11 -g -Wall -W -pedantic-errors

# With Sun's make it has to be done like this, instead of
# using wildcards.
# Well, I haven't figured out another way yet.
SOURCES = driver.cpp
HEADERS = Matrix.h Vector.h SOE_Solver.h OutOfRangeErr.h IncompatibleVectorErr.h IncompatibleMatrixErr.h Base_Matrix.h LowerTriangularMatrix.h UpperTriangularMatrix.h TridiagonalMatrix.h DiagonalMatrix.h SymmetricalMatrix.h

# Looks like it can be done like this, but won't work for gmake.
#SOURCES:sh = ls *.cpp
#HEADERS:sh = ls *.h

OBJECTS = $(SOURCES:%.cpp=%.o)

default: driver

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

driver: $(OBJECTS)
	@echo "Can we build $@?"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
	@echo ""
	@echo "Yes we can!"
	@echo ""

clean:
	-@rm -f core
	-@rm -f driver
	-@rm -f $(OBJECTS)

# Automatically generate dependencies and include them in Makefile
depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -MM *.cpp > $@


-include depend
