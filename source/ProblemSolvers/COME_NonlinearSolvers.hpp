#pragma once
#include "LinearAlgebra/COME_Linalg_sparse.hpp"

namespace NonlinearSolvers
{
	template <typename T>
	class NonlinearSolvers
	{
	public:
		//Default Constructor
		NonlinearSolvers(T tolerance = 1e-10, unsigned int max_iterations = 200) :
			tolerance_(tolerance), max_iterations_(max_iterations) {
		}
		//Copy constructor
		NonlinearSolvers(const NonlinearSolvers& other)
			: tolerance_(other.tolerance_), max_iterations_(other.max_iterations_) {
		}
		//Move constructor
		NonlinearSolvers(NonlinearSolvers&& other) noexcept
			: tolerance_(other.tolerance_), max_iterations_(other.max_iterations_) {
		}
		//Move Assignment operator
		NonlinearSolvers<T>& operator=(NonlinearSolvers&& other) noexcept;
		//Assignment operator
		NonlinearSolvers<T>& operator=(const NonlinearSolvers& other);

		LinearAlgebra::Vector<T>& NewtonMethodSolve() const;
		void setTolerance(T new_tolerance);
		void setIterationNumber(T newIterationNumber);
	private:
		T tolerance_;
		unsigned int max_iterations_;
		T beta_ = 0.5;
		T gamma_ = 0.01;

		T stepSizeArmillo();
		T stepSizePowellWolfe();
		void setBeta( T beta);
		void setGamma(T gamma);


	};

} //NonlinearSolvers