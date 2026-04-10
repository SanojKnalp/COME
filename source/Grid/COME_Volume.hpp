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
		void linkNodes(const std::array<int, 8>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap);
		void linkEdges(const std::array<int, 8>& nodes, std::map<std::pair<int, int>, Edge<dim, spacedim>*>& edgeMap);
		void linkFaces(const std::array<int, 8>& nodes, std::map<std::array<int, 4>, Face<dim, spacedim>*>& faceMap);

		std::vector<Node<dim, spacedim>*> getNodes() const;

	private:

		std::vector<Node<dim, spacedim>*>	listOfNodes_;
		std::vector<Edge<dim, spacedim>*>	listOfEdges_;
		std::vector<Face<dim, spacedim>*>	listOfFaces_;
		std::vector<Volume<dim, spacedim>*> listOfSubVolumes_;
	};

}