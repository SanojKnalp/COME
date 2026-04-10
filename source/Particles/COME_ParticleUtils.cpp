#include "COME_ParticleUtils.hpp"
#include <cassert>

namespace Particles
{
	template<int dim, typename Numbertype>
	Numbertype Point<dim, Numbertype>::operator()(const unsigned int index) const
	{
		assert(index >= 0);
		assert(index < dim);
		return coordinate_[index];
	}
	template<int dim, typename Numbertype>
	Point<dim, Numbertype>& Point<dim, Numbertype>::operator+=(Point<dim, Numbertype>& otherPoint)
	{
		for (int i = 0; i < dim; i++)
		{
			coordinate_[i] += otherPoint.coordinate_[i];
		}
		return *this;
	}

	template<int dim, typename Numbertype>
	Point<dim, Numbertype>& Point<dim, Numbertype>::operator-=(Point<dim, Numbertype>& otherPoint)
	{
		for (int i = 0; i < dim; i++)
		{
			coordinate_[i] -= otherPoint.coordinate_[i];
		}
		return *this;
	}

	template<int dim, typename Numbertype>
	bool Point<dim, Numbertype>::operator==(const Point<dim, Numbertype>& otherPoint) const
	{
		return coordinate_ == otherPoint.coordinate_;
	}

	template<int dim, typename Numbertype>
	Numbertype Point<dim, Numbertype>::norm_square() const
	{
		Numbertype sum = 0;
		for (int i = 0; i < dim; i++)
		{
			sum += coordinate_[i] * coordinate_[i];
		}
		return sqrt(sum);
	}

}