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
            int n2 = nodes[(i + 1) % 4]; 

            // Normalize for the edgeMap lookup
            auto [minN, maxN] = std::minmax(n1, n2);

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

    // this interpolation scheme is based on a simple combination of edge interpolations with a shared node
    template <int dim, int spacedim>
    std::array<double, spacedim> Face<dim, spacedim>::interpolate(unsigned int i, unsigned int p)
    {
        // ok, so we need basically a mapping to our grid
        /*
        * 6-7-8 3
        * 3-4-5 2
        * 0-1-2 1
        * 1 2 3       
        */
        // this is easy. Now we also need to find two edges that share a node.The easiest way is to pick a node and see if it's part of the edge.
        // if yes we take the two edges and do linear interpolation in each direction. that gives us then the coordinate
        // we simply pick a node from the list of nodes, and then find the other two points by simply checking if the node is part of 
        // we want to reuse our edge interpolation 

        unsigned int xIndex = i % (p - 1) +1;
        unsigned int yIndex = i/ (p - 1) + 1;

        std::array<double, spacedim> sharedNode = listOfNodes_[0]->getCoordinates();
        std::array<double, spacedim> interpolatedX;
        std::array<double, spacedim> interpolatedY;
        bool hit = false;
        for (const auto& edge : listOfEdges_)
        {
            for (const auto& node : edge->getListOfNodes())
            {
                if (node->getCoordinates() == sharedNode && !hit)
                {
                    interpolatedX = edge->interpolate(xIndex, p);
                    hit = true;
                }
                else if (node->getCoordinates() == sharedNode && hit)
                {
                    interpolatedY = edge->interpolate(yIndex, p);
                }
            }
        }

        std::array<double, spacedim> result;

        for (unsigned int d = 0; d < spacedim; ++d)
        {
            result[d] =
                sharedNode[d]
                + (interpolatedX[d] - sharedNode[d])
                + (interpolatedY[d] - sharedNode[d]);
        }

        return result;


    }

}

template class Mesh::Face<1>;
template class Mesh::Face<2>;
template class Mesh::Face<3>;
template class Mesh::Face<1,2>;
template class Mesh::Face<1,3>;
template class Mesh::Face<2,3>;