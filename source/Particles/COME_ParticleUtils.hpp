#pragma once

#include <array>

namespace Particles
{
	template <int dim, typename Numbertype = double>
	class Point
	{
	public:
		Point() : coordinate_({ 0,0,0 }) {};
		Point(const std::array<Numbertype, dim>& point) {};

		Numbertype operator()(const unsigned int index) const;
		Point<dim,Numbertype>& operator+=(Point<dim, Numbertype>& otherPoint);
		Point<dim,Numbertype>& operator-=(Point<dim, Numbertype>& otherPoint);
		bool operator==(const Point<dim, Numbertype>& otherPoint) const;

		Numbertype norm_square() const;


	private:
		std::array<Numbertype, dim> coordinate_;


	};
}