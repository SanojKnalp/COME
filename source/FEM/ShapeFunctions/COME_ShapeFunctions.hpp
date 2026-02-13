#pragma once
namespace ShapeFunctions
{
	template<int dim,int spacedim = dim>
	class ShapeFunctions
	{
	public:
		ShapeFunctions(unsigned int polynomial_degree)
			:polynomialDegree_(polynomial_degree) {}
		unsigned int getPolynomialDegree() const;
		virtual double get_shape_function_value(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_grad(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_grad_grad(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_third_derivative(const unsigned int index, const double qPointValue) const = 0;
		virtual double get_shape_function_fourth_derivative(const unsigned int index, const double qPointValue) const = 0;
	protected:
		unsigned int polynomialDegree_; //polynomial degree of the respective element

		

	};
	template<int dim,int spacedim>
	unsigned int ShapeFunctions<dim,spacedim>::getPolynomialDegree() const
	{
		return polynomialDegree_;
	}
}