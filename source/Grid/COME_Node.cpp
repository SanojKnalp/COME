#include "COME_Node.hpp"

template <int dim, int spacedim>
double Mesh::Node<dim,spacedim>::operator[](const unsigned int i)
{
	if ((i >= dim) ||(i<0))
	{
		throw std::runtime_error("You attempted to access a value outside of it's range.")
	}
	return coordinate_[i];
}



