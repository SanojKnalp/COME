# Changelog
All the changes i make to the code are documented here.
## 2026 
### February
#### 12.02.2026
Worked again on a bit of mesh stuff, especially the connection between AbsTopological Component and Element. Next step is finishing the element creation
#### 09.02.2026 
Worked a lot on mesh read in for abaqus and in general mesh functions. 
#### 07.02.2026
Added the functions inverse2x2() and inverse 3x3 that provide analytical formulations for the respective inverse matrices.
Also added tests for both.
Started working on reading in some meshes. Not the best experience so far.
#### 03.02.2026 
Added the first couple QGauss weights.
Added a bit of ascii art to the main for no reason :).
Added the Christoffelsymbols for spherical coordinates
#### 02.02.2026 
Started working on the abstract class Quadrature<dim> and a derived class QGauss<dim> which then later will be used for Quadrature.
Added a Test for the Jacobi Solver.
Added a Test for get_shape_function_value().
#### 01.02.2026
Finished the get_QP_grad_grad_degree_i() implementation
Finished the get_QP_third_derivative_degree_i() implementation
Finished the get_QP_fourth_derivative_degree_i() implementation