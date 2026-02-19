#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include "COME_Node.hpp"
#include <iostream>
#include <vector>

namespace Mesh
{
	template<int dim, int spacedim = dim>
	class Edge : public AbsTopologicalComponent<dim,spacedim>
	{
	public:
		Edge() = default;

		void linkNodes(std::array<int, 1 << spacedim>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap);
	private:
		std::vector<Node<dim,spacedim>*> listOfNodes_;
		std::vector<Edge<dim,spacedim>*> listOfSubEdges_;
	};
}