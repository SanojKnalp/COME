#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include <iostream>
#include <vector>

namespace Mesh
{
	template <int dim, int spacedim = dim>
	class Element 
	{
	public:
		void addTopologicalComponent(AbsTopologicalComponent<dim, spacedim>* comp);
		const std::vector<AbsTopologicalComponent<dim, spacedim>*>& getTopologicalSupport() const;

	private:
		std::vector<AbsTopologicalComponent<dim, spacedim>*> topologicalSupport_;
		std::vector<Element<dim,spacedim>*> listOfSubElements_;
	};
}