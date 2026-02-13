#include "COME_LinearIterativeSolvers.hpp"

namespace LinearSolvers
{

	template <typename T>
	void LinearIterativeSolvers<T>::set_tolerance(const T tolerance)
	{
		tolerance_ = tolerance;
	}

	template <typename T>
	void LinearIterativeSolvers<T>::set_maxIterations(const unsigned int maxIterations)
	{
		max_iterations_ = maxIterations;
	}
	
	template <typename T>
	void LinearIterativeSolvers<T>::set_smoothingFactor(const T SmoothingFactor)
	{
		smoothingFactor_ = SmoothingFactor;
	}

	template <typename T>
	LinearAlgebra::Vector<T> LinearIterativeSolvers<T>::JacobiSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& currentIterate) const
	{
		LinearAlgebra::SparseMatrix<T> D_inv = A.inverseDiagonalMatrix();
		for (int i = 0; i<max_iterations_ && (b - A * currentIterate).norm(2)>tolerance_; i++)
		{
			currentIterate = currentIterate + smoothingFactor_ * D_inv * (b - A * currentIterate);

		}
		return currentIterate;

	}
}

template class LinearSolvers::LinearIterativeSolvers<double>;
template class LinearSolvers::LinearIterativeSolvers<float>;