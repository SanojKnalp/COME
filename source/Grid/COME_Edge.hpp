#pragma once
#include "COME_AbsTopologicalComponent.hpp"
#include "COME_Node.hpp"
namespace Mesh
{
	template <int dim, int spacedim = dim>
	class Edge : public AbsTopologicalComponent
	{
	public:
		std::vector<Node<dim,spacedim>> ListOfNodes_;
		std::vector<Edge<dim,spacedim>> ListOfSubEdges_;

	private:

	};
}
