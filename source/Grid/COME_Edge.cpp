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

	template <int dim, int spacedim>
	std::array<double, spacedim> Edge<dim, spacedim>::interpolate(unsigned int i, unsigned int p)
	{
		double xi = -1.0 + 2.0 * i / p;
		double t = (xi + 1.0) / 2.0;
		std::array<double,spacedim> node0 = listOfNodes_[0]->getCoordinates();
		std::array<double,spacedim> node1 = listOfNodes_[1]->getCoordinates();
		std::array<double, spacedim> interpolated_node;
		for (int i = 0; i < spacedim; i++)
		{
			interpolated_node[i] = (1.0 - t) * node0[i] + t * node1[i];
		}
		return interpolated_node;
	}

	template <int dim, int spacedim>
	const std::vector<Node<dim, spacedim>*>& Edge<dim, spacedim>::getListOfNodes() const
	{
		return listOfNodes_;
	}
}

template class Mesh::Edge<1>;
template class Mesh::Edge<2>;
template class Mesh::Edge<3>;
template class Mesh::Edge<1,2>;
template class Mesh::Edge<1,3>;
template class Mesh::Edge<2,3>;
