#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include "COME_Edge.hpp"
#include "COME_Face.hpp"
#include "COME_Node.hpp"
#include <iostream>
#include <vector>

namespace Mesh
{
	template <int dim,int spacedim = dim>
	class Volume : public AbsTopologicalComponent<dim, spacedim>
	{
	public:
		Volume() = default;
		void linkNodes(std::array<int, 1 << spacedim>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap);

	private:

		std::vector<Node<dim, spacedim>*>	listOfNodes_;
		std::vector<Edge<dim, spacedim>*>	listOfEdges_;
		std::vector<Face<dim, spacedim>*>	listOfFaces_;
		std::vector<Volume<dim, spacedim>*> listOfSubVolumes_;
	};

}