# FEM
In this markdown i'll describe what i've learned about FEM while writing this solver
## Implementation 

### Relying on the work of others
In general, using the work already done by others is useful. Especially when it's done properly.
#### Linear Algebra - Armadillo
Armadillo was the first package i used in my FEM Solver and i don't regret it. It's just incredibly convenient to use.
When i started building my FEM solver, i had to make the decision of what i wanted to implement myself. In the end i decided to just go with a linear Algebra library.
Secondly i wanted a library that was incredibly easy to use. Those two points effectively eliminated Trilinos and PetSC and i went for Armadillo. 
The work done by Conrad Sanderson and Ryan Curtin was so incredibly useful i can't thank both enough. 
It immediately eliminated the pain of writing my own linear algebra library which would have taken weeks and months to do at least semi-properly.
## Theory 

## Computation 

#### Linear Solvers - SOR
Just because SOR is technically an option does not mean it's necessarily the most efficient choice. 
A simple argument against it is runtime. I need to use values i don't have in advance which is a huge drawback in contrast to other methods like CG or even standard Jacobi. 
Therefore i don't feel like adding it when we clearly see that it does not offer really a lot more than Jacobi despite being a lot more expensive to compute and less parallelizable.

## Application 
