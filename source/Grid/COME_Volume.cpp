#include "COME_Volume.hpp"

namespace Mesh
{
	template <int dim, int spacedim>
	void Volume<dim, spacedim>::linkNodes(std::array<int, 1 << spacedim>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap)
	{
		for (int i = 0; i < (1 << spacedim); i++)
		{
			listOfNodes_.push_back(nodeIdMap[nodes[i]]);

		}
	}
}

template class Mesh::Volume<3>;