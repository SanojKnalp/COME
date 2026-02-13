#include "COME_Quadrature_QGauss.hpp"


namespace Quadrature
{
	template <int dim>
	double QGauss<dim>::getQuadratureWeight() const
	{
		unsigned int index = 1; //remove later and do right
		switch (this->getQuadratureOrder())
		{
		case 1:	return get_QGauss_weight_degree_1(index);
		case 2:	return get_QGauss_weight_degree_2(index);
		case 3:	return get_QGauss_weight_degree_3(index);
		case 4:
		case 5:
		case 6:
		case 7:
		default:
			throw std::out_of_range("You tried to access a quadrature order of degree 8 or higher. This is not implemented as of right now.");
		}
	}

	//---------------------------------------------
	//----------- Quadrature weights --------------
	//---------------------------------------------

	//--------------- degree 1---------------------
	template <int dim>
	double QGauss<dim>::get_QGauss_weight_degree_1(unsigned int index) const
	{
		if (index > 0)
		{
			throw std::out_of_range("Invalid Quadrature index for QGauss1");
		}
		return 2.0;
	}

	//--------------- degree 2---------------------
	template <int dim>
	double QGauss<dim>::get_QGauss_weight_degree_2(unsigned int index) const
	{
		if (index > 1)
		{
			throw std::out_of_range("Invalid Quadrature index for QGauss2");
		}
		return 1.0;
	}

	//--------------- degree 3---------------------
	template <int dim>
	double QGauss<dim>::get_QGauss_weight_degree_3(unsigned int index) const
	{
		switch (index)
		{
		case 0: return 5.0 / 9.0;
		case 1:	return 8.0 / 9.0;
		case 2: return 5.0 / 9.0;
		default:
			throw std::out_of_range("Invalid Quadrature index for QGauss3");
		}
	}

}

template class Quadrature::QGauss<1>;
template class Quadrature::QGauss<2>;
template class Quadrature::QGauss<3>;