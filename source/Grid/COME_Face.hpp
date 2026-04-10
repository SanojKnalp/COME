#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include "COME_Edge.hpp"
#include "COME_Node.hpp"
#include <iostream>
#include <vector>
#include <map>

namespace Mesh
{
	template<int dim, int spacedim = dim>
	class Face : public AbsTopologicalComponent<dim,spacedim>
	{
	public:
		Face() = default;

		void linkNodes(const std::array<int, 4>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap);
		void linkEdges(const std::array<int, 4>& nodes, std::map<std::pair<int, int>, Edge<dim, spacedim>*>& edgeMap);

		std::array<double, spacedim> interpolate(unsigned int i, unsigned int p);
	private:
		std::vector<Node<dim,spacedim>*> listOfNodes_;
		std::vector<Edge<dim,spacedim>*> listOfEdges_;
		std::vector<Face<dim,spacedim>*> listOfSubFaces_;
	};
}
