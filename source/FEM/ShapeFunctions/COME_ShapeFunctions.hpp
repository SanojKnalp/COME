#pragma once
namespace ShapeFunctions
{
	template<int dim,int spacedim = dim>
	class ShapeFunctions
	{
	public:
		ShapeFunctions(unsigned int polynomial_degree, bool isDiscontinuous)
			:polynomialDegree_(polynomial_degree) , isDiscontinuous_(isDiscontinuous) {}
		unsigned int getPolynomialDegree() const;
		virtual double get_shape_function_value(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_grad(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_grad_grad(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_third_derivative(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_fourth_derivative(const unsigned int index, const double qPointValue) const = 0;

		void setPolynomialDegree(const unsigned int p);

		bool isDiscontinuous() const;

		unsigned int n_dofs_per_cell() const;
	protected:
		unsigned int polynomialDegree_; //polynomial degree of the respective element
		const bool isDiscontinuous_;   //DofHandler identifier if discontinuous or not. Used for DoF distribution

		

	};

	template <int dim, int spacedim>
	void ShapeFunctions<dim, spacedim>::setPolynomialDegree(const unsigned int p)
	{
		polynomialDegree_ = p;
	}
	template<int dim,int spacedim>
	unsigned int ShapeFunctions<dim,spacedim>::getPolynomialDegree() const
	{
		return polynomialDegree_;
	}

	template<int dim, int spacedim>
	bool ShapeFunctions<dim,spacedim>::isDiscontinuous() const
	{
		return isDiscontinuous_;
	}

	template <int dim, int spacedim>
	unsigned int ShapeFunctions<dim, spacedim>::n_dofs_per_cell() const
	{
		return (polynomialDegree_ + 1) ^ dim;
	}
}