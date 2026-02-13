#include "../catch.hpp"
#include "LinearSolvers/COME_LinearIterativeSolvers.hpp"

TEST_CASE("Jacobi Solver Test")
{
    // Setup the linear system
    LinearAlgebra::SparseMatrix<double> A(2, 2);
    LinearAlgebra::Vector<double> b(2);
    LinearAlgebra::Vector<double> x(2);

    x.set(0, 0.0);
    x.set(1, 0.0);

    A.set(0, 0, 2.0);
    A.set(1, 1, 2.0);
    A.set(0, 1, -1.0);
    A.set(1, 0, -1.0);

    b.set(0, 1.0);
    b.set(1, 1.0);

    // Create solver with tolerance and max iterations
    LinearSolvers::LinearIterativeSolvers<double> Jacobi_solver(1e-8,1.0, 100);

    SECTION("Jacobi solves correctly")
    {
        Jacobi_solver.JacobiSolve(A, b, x);

        // Check that the solution is within tolerance
        REQUIRE(Approx(x(0)).margin(1e-6) == 1.0);
        REQUIRE(Approx(x(1)).margin(1e-6) == 1.0);
    }
}
