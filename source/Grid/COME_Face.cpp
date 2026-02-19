#include "COME_Face.hpp"

namespace Mesh
{
	template <int dim, int spacedim>
	void Face<dim, spacedim>::linkNodes(std::array<int, 1 << spacedim>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap)
	{
		for (int i = 0; i < (1 << spacedim); i++)
		{
			listOfNodes_.push_back(nodeIdMap[nodes[i]]);

		}
	}
}

template class Mesh::Face<2>;
template class Mesh::Face<3>;
template class Mesh::Face<2,3>;