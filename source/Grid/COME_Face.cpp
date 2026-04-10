#include "COME_Face.hpp"

namespace Mesh
{
	template <int dim, int spacedim>
	void Face<dim, spacedim>::linkNodes(const std::array<int, 4>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap)
	{
		for (int i = 0; i < 4; i++)
		{
			listOfNodes_.push_back(nodeIdMap[nodes[i]]);

		}
	}

	template <int dim, int spacedim>
	void Face<dim, spacedim>::linkEdges(const std::array<int, 4>& nodes, std::map<std::pair<int, int>, Edge<dim, spacedim>*>& edgeMap)
	{
        // A quad face has 4 edges: (0,1), (1,2), (2,3), and (3,0)
        for (int i = 0; i < 4; ++i)
        {
            int n1 = nodes[i];
            int n2 = nodes[(i + 1) % 4]; // Wraps around to connect the last node to the first

            // Normalize for the edgeMap lookup
            auto [minN, maxN] = std::minmax(n1, n2);

            // Use find() to avoid the crash if an edge is missing
            auto it = edgeMap.find({ minN, maxN });
            if (it != edgeMap.end()) {
                this->listOfEdges_.push_back(it->second);
            }
            else {
                // If you get here, it means you're trying to add a face 
                // before its edges have been added to the edgeMap_!
                throw std::runtime_error("Edge not found in edgeMap during Face construction.");
            }
        }
	}
}

template class Mesh::Face<1>;
template class Mesh::Face<2>;
template class Mesh::Face<3>;
template class Mesh::Face<1,2>;
template class Mesh::Face<1,3>;
template class Mesh::Face<2,3>;