#pragma once
#include "COME_Quadrature.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
namespace Quadrature
{
	template <int dim>
	class QGauss : public Quadrature<dim>
	{
	public:
		QGauss(int order)
			: Quadrature<dim>(order)
		{}
		virtual std::vector<double> getQuadratureWeights() const;
		virtual std::vector<double> getQuadraturePoints() const;

	private:

		//------ quadrature weights --------------------------
		std::vector<double> get_QGauss_weight_degree_1() const;
		std::vector<double> get_QGauss_weight_degree_2() const;
		std::vector<double> get_QGauss_weight_degree_3() const;
		std::vector<double> get_QGauss_weight_degree_4() const;
		std::vector<double> get_QGauss_weight_degree_5() const;
		std::vector<double> get_QGauss_weight_degree_6() const;
		std::vector<double> get_QGauss_weight_degree_7() const;
		//------ quadrature points ---------------------------
		std::vector<double> get_QGauss_points_degree_1() const;
		std::vector<double> get_QGauss_points_degree_2() const;
		std::vector<double> get_QGauss_points_degree_3() const;
		std::vector<double> get_QGauss_points_degree_4() const;
		std::vector<double> get_QGauss_points_degree_5() const;
		std::vector<double> get_QGauss_points_degree_6() const;
		std::vector<double> get_QGauss_points_degree_7() const;

	};
}