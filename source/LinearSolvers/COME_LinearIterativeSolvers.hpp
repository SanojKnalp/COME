#include "COME_Linalg_sparse.h"
#include "COME_Linalg_vector.h"

namespace LinearSolvers {

	template<typename T>
	class LinearIterativeSolvers
	{
		LinearIterativeSolvers(T tolerance = 1e-6, T smoothingFactor = 1.0, unsigned int max_iterations = 100) :
			tolerance_(tolerance), smoothingFactor_(smoothingFactor), max_iterations_(max_iterations) 
		{}

		//The idea is to implement an adaptive Jacobi method.
		LinearAlgebra::Vector<T> JacobiSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& currentIterate, T smoothingFactor);
	private:
		T tolerance_;
		T smoothingFactor_;
		unsigned int max_iterations_;

	};

	template <typename T>
	LinearAlgebra::Vector<T> LinearIterativeSolvers<T>::JacobiSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& currentIterate, T smoothingFactor)
	{
		//fill with adaptive damped Jacobi
	}
}