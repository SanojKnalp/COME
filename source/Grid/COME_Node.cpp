#include "COME_Node.hpp"

namespace Mesh
{

	template<int dim, int spacedim>
	std::array<double, spacedim> Node<dim, spacedim>::getCoordinates() const
	{
		return position_;
	}
}

template class Mesh::Node<1>;
template class Mesh::Node<2>;
template class Mesh::Node<3>;
template class Mesh::Node<1, 2>;
template class Mesh::Node<1, 3>;
template class Mesh::Node<2, 3>;