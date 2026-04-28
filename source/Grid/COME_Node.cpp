#include "COME_Node.hpp"

namespace Mesh
{

	template<int dim, int spacedim>
	const std::array<double, spacedim> Node<dim, spacedim>::getCoordinates() const
	{
		return position_;
	}

	template <int dim, int spacedim>
	std::vector<Node<dim, spacedim>*> Node<dim,spacedim>::getNodes() const
	{
		return { const_cast<Node<dim, spacedim>*>(this) };
	}
}

template class Mesh::Node<1>;
template class Mesh::Node<2>;
template class Mesh::Node<3>;
template class Mesh::Node<1, 2>;
template class Mesh::Node<1, 3>;
template class Mesh::Node<2, 3>;