# CS328_Final_Project

This program can be run with three different primary methods that are outlined below:

!Operation Methods
Run as: ./driver <mesh_size> soe <Method>
<mesh_size> : The size of the mesh to use when solving the system.
<Method>    : 0 = Gauss Elimination
              3 = Cholesky Decomposition
           
Note: The numbers for <Method> are based on the enum values defined in SOE_Solver.h. Since the other matrix types can not represent this problem, they can not be used.


!Iterative Methods
Run as: ./driver <mesh_size> it <Method> <TOL> <Limit>
<mesh_size> : The size of the mesh to use when solving the system.
<Method>    : 0 = Jacobian
              1 = Gauss Seidel
<TOL>       : Specify the tolerance used when running the program.
<Limit>     : Iteration limit


!Special Method
Run as:  ./driver <mesh_size> spec <TOL> <Limit>
<mesh_size> : The size of the mesh to use when solving the system.
<TOL>       : Specify the tolerance used when running the program.
<Limit>     : Iteration limit



!General Note:
Be careful when choosing the mesh_size. The computation time for each method increases exponentially.
A (generally) safe value ranges from 10-100, however, 50 or so would probably be the best option. 


!How to generate graphs
This requires the use of gnuplots so make sure it is installed.
Open a terminal and navigate to the Run_Results directory. Run the following line:

    for f in *.txt; do gnuplot -e "file='${f%.*}'" gnuplot_cmd.gs; done
    
This will produce a graph for every .txt file in the directory, giving them the same name with the .png extension. 
