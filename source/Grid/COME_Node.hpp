#pragma once

#include "COME_AbsTopologicalComponent.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>


namespace Mesh
{
	template <int dim, int spacedim = dim>
	class Node : public AbsTopologicalComponent
	{
	public:
		double operator[](const unsigned int i);
	private:
		double coordinate_[dim];
		std::vector<Node> subNode_;
		


	};
}