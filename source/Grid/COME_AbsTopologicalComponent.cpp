#include "COME_AbsTopologicalComponent.hpp"


namespace Mesh
{
	template<int dim, int spacedim>
	void AbsTopologicalComponent<dim, spacedim>::addAdjacentElement(Element<dim, spacedim>* el)
	{
		listOfAdjacentElements_.push_back(el);
	}
	const std::vector<Element<dim, spacedim>*>& AbsTopologicalComponent<dim, spacedim>::getAdjacentElements() const
	{
		return listOfAdjacentElements_;
	}
}
