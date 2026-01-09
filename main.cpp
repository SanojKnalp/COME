#include "COME_Linalg_sparse.h"
#include "COME_Linalg_vector.h"
#include <iostream>

/*int main() {
    using namespace LinearAlgebra;

    // Create a 5x5 sparse matrix (all zeros for now)
    SparseMatrix<double> A(5, 5);

    // Create b = [1,1,1,1,1]^T
    Vector<double> b(5);
    for (size_t i = 0; i < 5; ++i) {
        b.set(i, 1.0);
    }

    // Initial guess x = [0,0,0,0,0]^T
    Vector<double> x(5);   // initialized to zeros by Armadillo

    // Compute residual r = b - A*x
    Vector<double> r = b - (A * x);

    // Print residual
    std::cout << "Residual r = b - A*x:" << std::endl;
    for (size_t i = 0; i < r.size(); ++i) {
        std::cout << r.get(i) << std::endl;
    }

    // Frobenius norm of A
    std::cout << "Frobenius norm of A: " << A.norm() << std::endl;

    // Scalar multiplication test
    SparseMatrix<double> B = A * 2.0;
    std::cout << "B(0,0) after scaling: " << B.get(0, 0) << std::endl;

    return 0;
}*/
