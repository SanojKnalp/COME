#pragma once
#include "COME_ShapeFunctions.hpp"
#include <stdexcept>
namespace ShapeFunctions
{
	template<int dim,int spacedim = dim>
	class FE_QP : public ShapeFunctions<dim,spacedim>
	{
	public:
		FE_QP(unsigned int polynomial_degree)
			: ShapeFunctions<dim, spacedim>(polynomial_degree, false)
		{}

		virtual double get_shape_function_value(const unsigned int index, const double qPointValue) const; //We only pass the quadrature value as we will use the abstract class ShapeFunctions to then later evaluate 
		virtual double get_shape_function_grad(const unsigned int index, const double qPointValue) const;
		virtual double get_shape_function_grad_grad(const unsigned int index, const double qPointValue) const;
		virtual double get_shape_function_third_derivative(const unsigned int index, const double qPointValue) const;
		virtual double get_shape_function_fourth_derivative(const unsigned int index, const double qPointValue) const;

	private:
		//--------- FE Polynomials------------------------------------------------------
		double get_QP_degree_1(const unsigned int index, const double qPointValue) const;
		double get_QP_degree_2(const unsigned int index, const double qPointValue) const;
		double get_QP_degree_3(const unsigned int index, const double qPointValue) const;
		double get_QP_degree_4(const unsigned int index, const double qPointValue) const;
		double get_QP_degree_5(const unsigned int index, const double qPointValue) const;
		double get_QP_degree_6(const unsigned int index, const double qPointValue) const;
		//--------- FE Polynomial grads ------------------------------------------------
		double get_QP_grad_degree_1(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_degree_2(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_degree_3(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_degree_4(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_degree_5(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_degree_6(const unsigned int index, const double qPointValue) const;
		//--------- FE Polynomial grad grads -------------------------------------------
		double get_QP_grad_grad_degree_1(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_grad_degree_2(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_grad_degree_3(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_grad_degree_4(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_grad_degree_5(const unsigned int index, const double qPointValue) const;
		double get_QP_grad_grad_degree_6(const unsigned int index, const double qPointValue) const;
		//--------- FE Polynomial third derivatives ------------------------------------
		double get_QP_third_derivative_degree_1(const unsigned int index, const double qPointValue) const;
		double get_QP_third_derivative_degree_2(const unsigned int index, const double qPointValue) const;
		double get_QP_third_derivative_degree_3(const unsigned int index, const double qPointValue) const;
		double get_QP_third_derivative_degree_4(const unsigned int index, const double qPointValue) const;
		double get_QP_third_derivative_degree_5(const unsigned int index, const double qPointValue) const;
		double get_QP_third_derivative_degree_6(const unsigned int index, const double qPointValue) const;
		//--------- FE Polynomial fourth derivatives -----------------------------------
		double get_QP_fourth_derivative_degree_1(const unsigned int index, const double qPointValue) const;
		double get_QP_fourth_derivative_degree_2(const unsigned int index, const double qPointValue) const;
		double get_QP_fourth_derivative_degree_3(const unsigned int index, const double qPointValue) const;
		double get_QP_fourth_derivative_degree_4(const unsigned int index, const double qPointValue) const;
		double get_QP_fourth_derivative_degree_5(const unsigned int index, const double qPointValue) const;
		double get_QP_fourth_derivative_degree_6(const unsigned int index, const double qPointValue) const;
		

	};

}