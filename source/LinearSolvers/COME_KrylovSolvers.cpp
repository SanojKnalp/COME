#include "COME_KrylovSolvers.hpp"

namespace LinearSolvers
{

	//Function that allows to modify the default tolerance
	template <typename T>
	void KrylovSolvers<T>::set_tolerance(T new_tolerance) {
		tolerance_ = new_tolerance;
	}

	template <typename T>
	T KrylovSolvers<T>::get_tolerance() const
	{
		return tolerance_;
	}

	//Function that allows to modify the default maximum number of iterations
	template <typename T>
	void KrylovSolvers<T>::set_max_iteration_number(unsigned int new_max_iteration_number)
	{
		max_iterations_ = new_max_iteration_number;
	}

	//Conjugate gradient solver function.
	template <typename T>
	LinearAlgebra::Vector<T>& KrylovSolvers<T>::conjugate_gradient_solve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess)
	{
		LinearAlgebra::Vector<T> residual = b - A * current_guess;
		LinearAlgebra::Vector<T> p_k = residual;
		LinearAlgebra::Vector<T> previous_residual;
		LinearAlgebra::Vector<T> Ap(b.size());
		for (int i = 0; i < max_iterations_; i++)
		{
			Ap = A * p_k;
			T alpha = (residual.dot(residual)) / (p_k.dot(Ap));
			current_guess = current_guess + alpha * p_k;
			previous_residual = residual;

			residual = residual - alpha * Ap;
			T normofResidual = residual.norm(2);
			storedResiduals_.push_back(normofResidual);
			if (normofResidual <= tolerance_)
			{
				last_step_ = i + 1;
				break;
			}

			T beta = (residual.dot(residual)) / (previous_residual.dot(previous_residual));
			p_k = residual + beta * p_k;

		}
		return current_guess;

	}

	//GMRES solver function
	template <typename T>
	LinearAlgebra::Vector<T>& KrylovSolvers<T>::GmresSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess) const
	{
		LinearAlgebra::Vector<T> residual = b - A * current_guess;
		T beta = residual.norm(2);
		T b_norm = b.norm(2);

		//need more time to do this properly
		return residual;

	}
}

template class LinearSolvers::KrylovSolvers<double>;
template class LinearSolvers::KrylovSolvers<float>;