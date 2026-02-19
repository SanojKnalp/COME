#include "COME_Element.hpp"

namespace Mesh
{
	template <int dim, int spacedim>
	void Element<dim,spacedim>::addTopologicalComponent(AbsTopologicalComponent<dim, spacedim>* comp)
	{
		topologicalSupport_ = comp;
		comp->addAdjacentElement(this);
	}

	template <int dim, int spacedim>
	const AbsTopologicalComponent<dim, spacedim>* Element<dim, spacedim>::getTopologicalSupport() const
	{
		return topologicalSupport_;
	}

	template <int dim, int spacedim>
	void Element<dim, spacedim>::setTopologicalSupport(AbsTopologicalComponent<dim, spacedim>* comp)
	{
		topologicalSupport_ = comp;
	}
}

template class Mesh::Element<1>;
template class Mesh::Element<2>;
template class Mesh::Element<3>;
template class Mesh::Element<1,2>;
template class Mesh::Element<1,3>;
template class Mesh::Element<2,3>;
