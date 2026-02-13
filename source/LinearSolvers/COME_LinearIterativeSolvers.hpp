#include "LinearAlgebra/COME_Linalg_sparse.hpp"
#include "LinearAlgebra/COME_Linalg_vector.hpp"

namespace LinearSolvers {

	template<typename T>
	class LinearIterativeSolvers
	{
	public:
		LinearIterativeSolvers(T tolerance = 1e-6, T smoothingFactor = 1.0, unsigned int max_iterations = 100) :
			tolerance_(tolerance), smoothingFactor_(smoothingFactor), max_iterations_(max_iterations) 
		{}

		//The idea is to implement a Jacobi method.
		LinearAlgebra::Vector<T> JacobiSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& currentIterate) const;
		void set_tolerance(const T tolerance);
		void set_maxIterations(const unsigned int maxIterations);
		void set_smoothingFactor(const T smoothingFactor);
	private:
		T tolerance_;
		T smoothingFactor_;
		unsigned int max_iterations_;

	};


}