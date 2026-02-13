#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include <iostream>
#include <array>

namespace Mesh
{
	template<int dim, int spacedim = dim>
	class Node : public AbsTopologicalComponent<dim,spacedim>
	{
	public:
		Node(int id, std::array<double, spacedim> position) :
			meshid_(id), position_(position) {
		}
		std::array<double, spacedim> getCoordinates()const ;
		int getMeshid() const;
	private:
		std::array<double,spacedim> position_;
		int meshid_;
		Node* subNode_;

	};

	
}