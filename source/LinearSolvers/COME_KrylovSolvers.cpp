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
	LinearAlgebra::Vector<T>& KrylovSolvers<T>::GmresSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess)
	{
		// 1. Initial Setup
		LinearAlgebra::Vector<T> r = b - (A * current_guess);
		T beta = r.norm(2);
		if (beta < tolerance_) return current_guess;

		std::vector<LinearAlgebra::Vector<T>> V;
		V.push_back(r * (1.0 / beta));

		// H will be (m+1) x m. g stores the projected RHS.
		LinearAlgebra::FullMatrix<T> H(max_iterations_ + 1, max_iterations_);
		LinearAlgebra::Vector<T> g(max_iterations_ + 1);
		g(0) = beta;

		// Vectors to store Givens rotations (cosines and sines)
		std::vector<T> cs(max_iterations_, 0);
		std::vector<T> sn(max_iterations_, 0);

		int final_j = 0;

		for (int j = 0; j < max_iterations_; j++)
		{
			final_j = j;

			// --- Arnoldi Step ---
			LinearAlgebra::Vector<T> q = A * V[j];
			for (int i = 0; i <= j; i++)
			{
				H(i, j) = V[i].dot(q);
				q = q - (H(i, j) * V[i]);
			}
			H(j + 1, j) = q.norm(2);
			V.push_back(q * (1.0 / H(j + 1, j)));

			// --- Apply Previous Givens Rotations to the new column of H ---
			for (int i = 0; i < j; i++)
			{
				T temp = cs[i] * H(i, j) + sn[i] * H(i + 1, j);
				H(i + 1, j) = -sn[i] * H(i, j) + cs[i] * H(i + 1, j);
				H(i, j) = temp;
			}

			// --- Generate New Givens Rotation to zero out H(j+1, j) ---
			T a = H(j, j);
			T b_val = H(j + 1, j);
			if (std::abs(b_val) < 1e-15) {
				cs[j] = 1.0; sn[j] = 0.0;
			}
			else if (std::abs(b_val) > std::abs(a)) {
				T tau = a / b_val;
				sn[j] = 1.0 / std::sqrt(1.0 + tau * tau);
				cs[j] = sn[j] * tau;
			}
			else {
				T tau = b_val / a;
				cs[j] = 1.0 / std::sqrt(1.0 + tau * tau);
				sn[j] = cs[j] * tau;
			}

			// --- Apply New Rotation to H and g ---
			H(j, j) = cs[j] * H(j, j) + sn[j] * H(j + 1, j);
			H(j + 1, j) = 0.0; // This is now zeroed out

			g(j + 1) = -sn[j] * g(j);
			g(j) = cs[j] * g(j);

			// The absolute value of g(j+1) is the current residual norm!
			if (std::abs(g(j + 1)) < tolerance_) break;
		}

		// --- Back Substitution to solve Hy = g ---
		// At this point H is upper triangular (R)
		LinearAlgebra::Vector<T> y(final_j + 1);
		for (int i = final_j; i >= 0; i--)
		{
			T sum = 0;
			for (int k = i + 1; k <= final_j; k++) {
				sum += H(i, k) * y(k);
			}
			y(i) = (g(i) - sum) / H(i, i);
		}

		// --- Update Solution: x = x0 + V*y ---
		for (int i = 0; i <= final_j; i++) {
			current_guess = current_guess + (V[i] * y(i));
		}

		return current_guess;
	}

	//BiCGStab solver function
	/*
	For this function we follow exactly the version shown at Wikipedia.
	*/
	template <typename T>
	LinearAlgebra::Vector<T>& KrylovSolvers<T>::BiCGStabSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess)
	{
		// 1. Setup
		LinearAlgebra::Vector<T> residual = b - A * current_guess;
		LinearAlgebra::Vector<T> r_hat = residual;

		T rho = residual.dot(r_hat);
		LinearAlgebra::Vector<T> p = residual;
		LinearAlgebra::Vector<T> v(residual.size()), s(residual.size()), t(residual.size()), h(residual.size());

		for (int i = 0; i < max_iterations_; i++)
		{
			// Follow exactly Wikipedia
			v = A * p;
			T alpha = rho / (r_hat.dot(v));
			h = current_guess + alpha * p;
			s = residual - alpha * v;
			if (s.norm(2) <= tolerance_)
			{
				current_guess = h;
				return current_guess;
			}
			t = A * s;
			T omega = (t.dot(s)) / (t.dot(t));
			current_guess = h + omega * s;
			residual = s - omega * t;
			if (residual.norm(2) <= tolerance_)
			{
				return current_guess;
			}
			T rho_next = r_hat.dot(residual);

			T beta = (alpha / omega) * (rho_next / rho);
			p = residual + beta * (p - omega * v);
			rho = rho_next;
		}
		return current_guess;

	}

	template <typename T>
	LinearAlgebra::Vector<T>& KrylovSolvers<T>::MINRESSolve(const LinearAlgebra::SparseMatrix<T>& A, const LinearAlgebra::Vector<T>& b, LinearAlgebra::Vector<T>& current_guess)
	{
		// 1. Initial Setup
		LinearAlgebra::Vector<T> residual = b - A * current_guess;
		LinearAlgebra::Vector<T> v_prev(residual.size()); // v_{k-1} (starts as 0)
		LinearAlgebra::Vector<T> v = residual;                 // v_k
		T beta = v.norm(2);

		// Handle the edge case where the initial guess is already perfect
		if (beta <= tolerance_) {
			return current_guess;
		}

		v = (1/beta) * v; // Normalize the first Lanczos vector

		// Vectors to hold the search directions (w)
		LinearAlgebra::Vector<T> w_prev2(residual.size()); // w_{k-2}
		LinearAlgebra::Vector<T> w_prev(residual.size());  // w_{k-1}
		LinearAlgebra::Vector<T> w(residual.size());       // w_k

		T c = 1.0, c_prev = 1.0;
		T s = 0.0, s_prev = 0.0;
		T eta = beta; 
		LinearAlgebra::Vector<T> q(residual.size());

		for (int i = 0; i < max_iterations_; i++)
		{
			q = A * v;
			T alpha = v.dot(q);

			q = q - (alpha * v) - (beta * v_prev);
			T beta_next = q.norm(2);

			T t0 = c * alpha - c_prev * s * beta;
			T t1 = s * alpha + c_prev * c * beta;
			T t2 = s_prev * beta;

			// Calculate new rotation to zero out the subdiagonal element (beta_next)
			T gamma = std::sqrt(t0 * t0 + beta_next * beta_next);
			c_prev = c;
			s_prev = s;
			c = t0 / gamma;
			s = beta_next / gamma;

			w = (1/gamma) * (v - (t1 * w_prev) - (t2 * w_prev2));
			current_guess += (c * eta) * w;

			// Update the residual tracker (eta decreases as we converge)
			eta = -s * eta;

			// Check for convergence without needing to calculate the full residual norm
			if (std::abs(eta) <= tolerance_) {
				return current_guess;
			}

			v_prev = v;
			v = (1/ beta_next) * q ;
			beta = beta_next;

			w_prev2 = w_prev;
			w_prev = w;
		}

		return current_guess;
	}
}

template class LinearSolvers::KrylovSolvers<double>;
template class LinearSolvers::KrylovSolvers<float>;