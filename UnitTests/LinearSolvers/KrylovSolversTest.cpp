#include "../catch.hpp"
#include "LinearSolvers/COME_KrylovSolvers.hpp"

TEST_CASE("Conjugate Gradient Solver Test", "[conjugate_gradient]")
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
    LinearSolvers::KrylovSolvers<double> CG_solver(1e-8, 30);

    SECTION("Conjugate gradient solves correctly")
    {
        CG_solver.conjugate_gradient_solve(A, b, x);

        // Check that the solution is within tolerance
        REQUIRE(Approx(x(0)).margin(1e-6) == 1.0);
        REQUIRE(Approx(x(1)).margin(1e-6) == 1.0);
    }
}

TEST_CASE("BiCGStab Solver Test", "[bicgstab]")
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
    LinearSolvers::KrylovSolvers<double> bicgstab_solver(1e-8, 30);

    SECTION("bicgstab solves correctly")
    {
        bicgstab_solver.BiCGStabSolve(A, b, x);

        // Check that the solution is within tolerance
        REQUIRE(Approx(x(0)).margin(1e-6) == 1.0);
        REQUIRE(Approx(x(1)).margin(1e-6) == 1.0);
    }
}

TEST_CASE("GMRES Solver Test", "[gmres]")
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
    LinearSolvers::KrylovSolvers<double> gmres_solver(1e-8, 30);

    SECTION("gmres solves correctly")
    {
        gmres_solver.GmresSolve(A, b, x);

        // Check that the solution is within tolerance
        REQUIRE(Approx(x(0)).margin(1e-6) == 1.0);
        REQUIRE(Approx(x(1)).margin(1e-6) == 1.0);
    }
}

TEST_CASE("MINRES Solver Test", "[minres]")
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
    LinearSolvers::KrylovSolvers<double> minres_solver(1e-8, 30);

    SECTION("minres solves correctly")
    {
        minres_solver.MINRESSolve(A, b, x);

        // Check that the solution is within tolerance
        REQUIRE(Approx(x(0)).margin(1e-6) == 1.0);
        REQUIRE(Approx(x(1)).margin(1e-6) == 1.0);
    }
}
