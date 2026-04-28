#pragma once
#include "FEM/ShapeFunctions/COME_ShapeFunctions.hpp"
#include "FEM/Quadrature/COME_Quadrature.hpp"
#include "Grid/COME_AbsTopologicalComponent.hpp"

#include <array>
#include <vector>
#include <iostream>

namespace Mesh {
	template<int dim, int spacedim>
	class AbsTopologicalComponent;
}

namespace FEM
{
	template<int dim, int spacedim = dim>
	class FEValues
	{
	public:
		FEValues(ShapeFunctions::ShapeFunctions<dim, spacedim>& fe, Quadrature::Quadrature<dim>& quadrature, bool update_values = true)
			: fe_(fe)
			, quadrature_(quadrature)
			, update_values_(update_values)
		{
			TensorProductQPointsAndWeights();
		}

		const double& shape_value(const unsigned int index, const unsigned int q_point) const;
		const double& JxW(const unsigned int q_point) const;
		void reinit(const Mesh::AbsTopologicalComponent<dim,spacedim>& cell);

	private:

		ShapeFunctions::ShapeFunctions<dim, spacedim>& fe_;
		Quadrature::Quadrature<dim>& quadrature_;
		const bool update_values_;
		std::vector<std::array<double, dim>> qPoints_;
		std::vector<double> qWeights_;
		std::vector<std::array<double, spacedim>> cell_nodes;



		double TensorproductShapeFunctionsValue(const unsigned int index, std::array<double,dim>& localPoints) const;
		void TensorProductQPointsAndWeights();
		double JacobianDeterminant();

	};

	template <int dim, int spacedim>
	void FEValues<dim, spacedim>::TensorProductQPointsAndWeights()
	{
		std::vector<double> qPoints = quadrature_.getQuadraturePoints();
		std::vector<double> qWeights = quadrature_.getQuadratureWeights();
		int size = qPoints.size();

		if constexpr (dim == 1)
		{
			for (int i = 0; i < size; i++)
			{

				qPoints_.push_back(std::array<double, dim>{ qPoints[i] });
			}
			qWeights_ = qWeights;
		}
		if constexpr (dim == 2)
		{

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					qPoints_.push_back(std::array<double, dim>{ qPoints[i], qPoints[j] });
					qWeights_.push_back(qWeights[i] * qWeights[j]);
				}
			}

		}
		if constexpr (dim == 3)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					for (int k = 0; k < size; k++)
					{
						qPoints_.push_back( std::array<double, dim>{qPoints[i], qPoints[j], qPoints[k]});
						qWeights_.push_back(qWeights[i] * qWeights[j] * qWeights[k]);
					}
				}
			}

		}
	}

	template <int dim, int spacedim>
	void FEValues<dim, spacedim>::reinit(const Mesh::AbsTopologicalComponent<dim, spacedim>& cell)
	{
		cell_nodes.clear();
		for (auto& node : cell.getNodes())
		{
			cell_nodes.push_back(node->getCoordinates());
		}
	}
}