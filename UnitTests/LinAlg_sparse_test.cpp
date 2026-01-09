#include "COME_Linalg_sparse.h"
#include "COME_Linalg_vector.h"
#include <iostream>
#include <random>
#include <cmath>

// Helper: fill a Vector<double> with random values
void fill_random(LinearAlgebra::Vector<double>& v) {
    static std::mt19937 rng(12345);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (size_t i = 0; i < v.size(); ++i) {
        v(i) = dist(rng);
    }
}

int linalg_sparse_test_residual() {
    using namespace LinearAlgebra;

    SparseMatrix<double> A(5, 5);

    Vector<double> x(5);
    Vector<double> b(5);

    fill_random(x);
    fill_random(b);

    Vector<double> r = b - (A * x);

    for (size_t i = 0; i < r.size(); ++i) {
        std::cout << r(i) << std::endl;
    }

    return 0;
}

bool linalg_sparse_test_frobenius_norm() {
    using namespace LinearAlgebra;

    SparseMatrix<double> A(5, 5);

    // use set(row,col) which returns a T&
    A.set(0, 0, 5.0);
    A.set(1, 1,1.0);
    A.set(2, 2,2.0);
    A.set(3, 3,3.0);
    A.set(4, 4,4.0);

    double frob = A.norm();

    // sqrt(5² + 1² + 2² + 3² + 4²) = sqrt(55)
    return std::abs(frob - std::sqrt(55.0)) < 1e-12;
}

bool linalg_sparse_test_smult() {
    using namespace LinearAlgebra;

    SparseMatrix<double> A(5, 5);


    A.set(0, 0, 5.0);
    A.set(1, 1, 1.0);
    A.set(2, 2, 2.0);
    A.set(3, 3, 3.0);
    A.set(4, 4, 4.0);

    double factor = 2.0;

    SparseMatrix<double> B = A * factor;

    return B(1, 1) == 2.0 * A(1, 1);
}
