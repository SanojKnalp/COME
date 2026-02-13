#include "COME_NonlinearSolvers.hpp"

namespace NonlinearSolvers
{
	template <typename T>
	T NonlinearSolvers<T>::stepSizeArmillo()
	{
		return 0;
	}

	template<typename T>
	T NonlinearSolvers<T>::stepSizePowellWolfe()
	{
		return 0.0;
	}
	/*template< typename T>
	LinearAlgebra::Vector<T>& NonlinearSolvers<T>::NewtonMethodSolve() const
	{
		return ;
	}*/
	template <typename T>
	void NonlinearSolvers<T>::setTolerance(T new_tolerance)
	{
		tolerance_ = new_tolerance;
	}
	template <typename T>
	void NonlinearSolvers<T>::setIterationNumber(T newIterationNumber)
	{
		max_iterations_ = newIterationNumber;
	}

	template <typename T>
	NonlinearSolvers<T>& NonlinearSolvers<T>::operator=(NonlinearSolvers&& other) noexcept
	{
		if (this != &other)
		{
			tolerance_ = other.tolerance_;
			max_iterations_ = other.max_iterations_;
			other.tolerance_ = 0.0;
			other.max_iterations_ = 0;

		}
		return *this;
	}
	template <typename T>
	NonlinearSolvers<T>& NonlinearSolvers<T>::operator=(const NonlinearSolvers<T>& other)
	{
		if (this != &other)
		{
			tolerance_ = other.tolerance_;
			max_iterations_ = other.max_iterations_;
		}
		return *this;
	}

	template <typename T>
	void NonlinearSolvers<T>::setBeta(T beta)
	{
		beta_ = beta;
	}

	template <typename T>
	void NonlinearSolvers<T>::setGamma(T gamma)
	{
		gamma_ = gamma;
	}
}

template class NonlinearSolvers::NonlinearSolvers<double>;
template class NonlinearSolvers::NonlinearSolvers<float>;