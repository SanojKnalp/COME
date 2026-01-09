#pragma once
#include "COME_Linalg_vector.h"
#include "COME_Linalg_sparse.h"

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
		LinearAlgebra::Vector<T>& conjugate_gradient_solve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess) const;
		void set_tolerance(T new_tolerance);
		T get_tolerance() const;
		void set_max_iteration_number(unsigned int new_max_iteration_number);
		//Assignment operator
		KrylovSolvers<T>& operator=(const KrylovSolvers& other);
		//Move assignment operator
		KrylovSolvers<T>& operator=(KrylovSolvers&& other) noexcept;
		

	private:
		T tolerance_;
		unsigned int max_iterations_;
		std::vector<T> storedResiduals_;
		unsigned int last_step_;
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
			last_step = other.last_step_;
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
			last_step = other.last_step_;
			other.last_step_ = 0;
		}
		return *this;
	}

	



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
	LinearAlgebra::Vector<T>& KrylovSolvers<T>::conjugate_gradient_solve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess) const
	{
		LinearAlgebra::Vector<T> residual = b - A * current_guess;
		LinearAlgebra::Vector<T> p_k = residual;
		LinearAlgebra::Vector<T> previous_residual;
		LinearAlgebra::Vector<T> Ap(b.size());
		for (int i = 0; i < max_iterations_; i++)
		{
			Ap= A * p_k;
			T alpha = (residual.dot(residual)) / (p_k.dot(Ap));
			current_guess = current_guess + alpha * p_k  ;
			previous_residual = residual;
			
			residual = residual - alpha * Ap;
			T normofResidual = residual.norm(2);
			storedResiduals_.push_back(normofResidual);
			if (normofResidual <= tolerance_)
			{
				break;
			}
			
			T beta = (residual.dot(residual))/(previous_residual.dot(previous_residual));
			p_k = residual + beta * p_k;

		}
		return current_guess;

	}







}