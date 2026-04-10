#include "COME_Edge.hpp"

namespace Mesh
{
	template <int dim, int spacedim>
	void Edge<dim, spacedim>::linkNodes(const std::array<int, 2>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap)
	{
		for (int i = 0; i < 2; i++)
		{
			listOfNodes_.push_back(nodeIdMap[nodes[i]]);
		}
	}
}

template class Mesh::Edge<1>;
template class Mesh::Edge<2>;
template class Mesh::Edge<3>;
template class Mesh::Edge<1,2>;
template class Mesh::Edge<1,3>;
template class Mesh::Edge<2,3>;
