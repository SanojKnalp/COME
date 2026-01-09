#include "COME_Linalg_sparse.h"
#include "COME_Linalg_vector.h"
#include <cmath>
namespace eigenvalueComputation
{
	template <typename T>
	class eigenvalueComputation
	{
	private:
		T tolerance_;
	public:
		LinearAlgebra::Vector<T> analytical_eigenvalue_computation(const LinearAlgebra::SparseMatrix<T>& A);
		T power_method(const LinearAlgebra::SparseMatrix<T>& A, LinearAlgebra::Vector<T>& b);


	};

	template < typename T>
	LinearAlgebra::Vector<T> analytical_eigenvalue_computation(const LinearAlgebra::SparseMatrix<T>& A)
	{

	}

	template < typename T>
	T eigenvalueComputation<T>::power_method( const LinearAlgebra::SparseMatrix<T>& A, LinearAlgebra::Vector<T>& b)
	{

	}

	

	
}
