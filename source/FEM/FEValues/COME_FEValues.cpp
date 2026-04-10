#include "COME_FEValues.hpp"

namespace FEM
{
	template <int dim, int spacedim>
	double FEValues<dim, spacedim>::TensorproductShapeFunctionsValue(const unsigned int index, std::array<double, dim>& localPoints) const
	{
		double value = 1.0;
		unsigned int temp_index = index;
		n = fe_.getPolynomialDegree() + 1;
		for (int i = 0; i < dim; i++)
		{
			int localIndex = temp_index % n;
			temp_index /= n;
			value *= fe_.get_shape_function_value(localIndex, localPoints[i]);
		}
		return value;
	}

	template <int dim, int spacedim>
	const double& FEValues<dim,spacedim>::shape_value(const unsigned int index, const unsigned int q_point) const
	{
		return TensorProductShapeFunctionsValue(index, qPoints_[q_point]);
	}

	template <int dim, int spacedim>
	double FEValues<dim, spacedim>::JacobianDeterminant()
	{

	}

	
	template <int dim, int spacedim>
	const double& FEValues<dim, spacedim>::JxW(const unsigned int q_point) const
	{
		return qWeights_[q_point]; // we still need the jacobian

	}
}

template class FEM::FEValues<1>;
template class FEM::FEValues<2>;
template class FEM::FEValues<3>;
template class FEM::FEValues<1,2>;
template class FEM::FEValues<1,3>;
template class FEM::FEValues<2,3>;