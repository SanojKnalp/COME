#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include "COME_Edge.hpp"
#include "COME_Node.hpp"
#include <iostream>
#include <vector>

namespace Mesh
{
	template<int dim, int spacedim = dim>
	class Face : public AbsTopologicalComponent<dim,spacedim>
	{
	public:
		Face() = default;

		void linkNodes(std::array<int, 1 << spacedim>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap);
	private:
		std::vector<Node<dim,spacedim>*> listOfNodes_;
		std::vector<Edge<dim,spacedim>*> listOfEdges_;
		std::vector<Face<dim,spacedim>*> listOfSubFaces_;
	};
}
