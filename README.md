# CS328_Final_Project

This program can be run with three different primary methods that are outlined below:

Poisson Equation Solver
Run as: ./driver <mesh_size> soe <Method>
<mesh_size> : The size of the mesh to use when solving the system.
<Method> : 0 = 


Iterative Methods
Run as: ./driver <mesh_size> it <Method> <TOL> <Limit>
<mesh_size> : The size of the mesh to use when solving the system.
<Method> : 0 = Jacobian
           1 = Gauss Seidel
<TOL> : Specify the tolerance used when running the program.
<Limit> : 


Special Method
Run as:  ./driver <mesh_size> spec <TOL> <Limit>
<mesh_size> : The size of the mesh to use when solving the system.
<TOL> : Specify the tolerance used when running the program.
<Limit> : 



General Note:
Be careful when choosing the mesh_size. The computation time for each method increases exponentially.
A (generally) safe value ranges from 10-100, however, 50 or so would probably be the best option. 