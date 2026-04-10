#pragma once
#include "LinearAlgebra/COME_Linalg_vector.hpp"
#include "LinearAlgebra/COME_Linalg_sparse.hpp"
#include "LinearAlgebra/COME_Linalg_dense.hpp"
#include <iostream>
#include <vector>
#include <cmath>

namespace LinearSolvers {

	template <typename T>
	class KrylovSolvers {
	public: 
		//Constructor
		KrylovSolvers(T tol = 1e-6, unsigned int max_iter = 100)
			: tolerance_(tol), max_iterations_(max_iter), storedResiduals_({}), last_step_(0) {
		}
		//Copy Constructor
		KrylovSolvers(const KrylovSolvers& other);
		//Move Constructor
		KrylovSolvers(KrylovSolvers&& other) noexcept;

		//Assignment operator
		KrylovSolvers<T>& operator=(const KrylovSolvers& other);
		//Move assignment operator
		KrylovSolvers<T>& operator=(KrylovSolvers&& other) noexcept;

		void set_tolerance(T new_tolerance);
		T get_tolerance() const;
		void set_max_iteration_number(unsigned int new_max_iteration_number);

		LinearAlgebra::Vector<T>& conjugate_gradient_solve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess);
		LinearAlgebra::Vector<T>& GmresSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess);
		LinearAlgebra::Vector<T>& BiCGStabSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess);
		LinearAlgebra::Vector<T>& MINRESSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess);
		

	private:
		T tolerance_;
		unsigned int max_iterations_;
		std::vector<T> storedResiduals_;
		unsigned int last_step_;				//just to track after how many iterations CG converged.
	};

	//Copy constructor
	template< typename T>
	KrylovSolvers<T>::KrylovSolvers(const KrylovSolvers& other)
		: tolerance_(other.tolerance_),max_iterations_(other.max_iterations_), storedResiduals_(other.storedResiduals_),last_step_(other.last_step_)
	{}
	//Move constructor
	template<typename T>
	KrylovSolvers<T>::KrylovSolvers(KrylovSolvers&& other) noexcept
		: tolerance_(other.tolerance_),
		max_iterations_(other.max_iterations_),
		storedResiduals_(std::move(other.storedResiduals_)),
		last_step_(other.last_step_)
	{}

	//Assignment operator
	template <typename T>
	KrylovSolvers<T>& KrylovSolvers<T>::operator=(const KrylovSolvers& other)
	{
		if (this != &other)
		{
			tolerance_ = other.tolerance_;
			max_iterations_ = other.max_iterations_;
			storedResiduals_ = other.storedResiduals_;
			last_step_ = other.last_step_;
		}
		return *this;
	}
	//Move assignment operator
	template< typename T>
	KrylovSolvers<T>& KrylovSolvers<T>::operator=(KrylovSolvers&& other) noexcept
	{
		if (this != &other)
		{
			tolerance_ = other.tolerance_;
			other.tolerance_ = 0.0;
			max_iterations_ = other.max_iterations_;
			other.max_iterations_ = 0;
			storedResiduals_ = std::move(other.storedResiduals_);
			last_step_ = other.last_step_;
			other.last_step_ = 0;
		}
		return *this;
	}


}