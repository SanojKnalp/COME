#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include "COME_Node.hpp"
#include "COME_Edge.hpp"

namespace Mesh
{
	template <int dim>
	class Face
	{
	public:

	private:
		std::vector<Node<dim>> listOfNodes_;
		std::vector<Edge<dim>> listOfEdges_;
		std::vector<Face<dim>> listOfSubfaces_;
	};
}
