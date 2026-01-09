#include "COME_KrylovSolvers.hpp"

bool conjugate_gradient_test()
{
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

	LinearSolvers::KrylovSolvers<double> CG_solver;
	CG_solver = LinearSolvers::KrylovSolvers<double>(1e-8, 30);
	std::cout << "tolerance_" << CG_solver.get_tolerance() << std::endl;
	CG_solver.conjugate_gradient_solve(A, b, x);
	if (((x(0) - 1.0) <= 1e-6) && ((x(1) - 1.0) <= 1e-6))
	{
		return true;
	}
	return false;

}

int main()
{
	if (conjugate_gradient_test() == true)
	{
		std::cout << "Test successful" << std::endl;
	}
	return 0;
}