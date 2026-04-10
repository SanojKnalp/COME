#include "COME_Volume.hpp"

namespace Mesh
{
	template <int dim, int spacedim>
	void Volume<dim, spacedim>::linkNodes(const std::array<int, 8>& nodes, std::unordered_map<int, Node<dim, spacedim>*>& nodeIdMap)
	{
		for (int i = 0; i < 8; i++)
		{
			listOfNodes_.push_back(nodeIdMap[nodes[i]]);

		}
	}

	template <int dim, int spacedim>
    void Volume<dim, spacedim>::linkEdges(const std::array<int, 8>& nodes, std::map<std::pair<int, int>, Edge<dim, spacedim>*>& edgeMap)
    {
        // A simple way to define the 12 edges of a standard hex cell by node indices
        const std::vector<std::pair<int, int>> localEdgeMap = {
            {0,1}, {1,2}, {2,3}, {3,0}, // Bottom face
            {4,5}, {5,6}, {6,7}, {7,4}, // Top face
            {0,4}, {1,5}, {2,6}, {3,7}  // Vertical pillars
        };

        for (auto& localEdge : localEdgeMap) {
            auto [minN, maxN] = std::minmax(nodes[localEdge.first], nodes[localEdge.second]);
            this->listOfEdges_.push_back(edgeMap.at({ minN, maxN }));
        }

        

    }

    template <int dim, int spacedim>
    void Volume<dim, spacedim>::linkFaces(const std::array<int, 8>& nodes, std::map<std::array<int, 4>, Face<dim, spacedim>*>& faceMap)
    {
        // 1. Define the 6 faces of a hexahedron by their local node indices
        // Standard VTK/Finite Element ordering for a Hex8:
        static const std::array<std::array<int, 4>, 6> localFaceIndices = { {
            {0, 3, 2, 1}, // Bottom
            {4, 5, 6, 7}, // Top
            {0, 1, 5, 4}, // Front
            {1, 2, 6, 5}, // Right
            {2, 3, 7, 6}, // Back
            {3, 0, 4, 7}  // Left
        } };

        for (const auto& localIndices : localFaceIndices)
        {
            // 2. Extract global node IDs for this face
            int nA = nodes[localIndices[0]];
            int nB = nodes[localIndices[1]];
            int nC = nodes[localIndices[2]];
            int nD = nodes[localIndices[3]];

            // 3. Sort them to match the faceMap_ key format (Ascending)
            if (nA > nB) std::swap(nA, nB);
            if (nC > nD) std::swap(nC, nD);
            if (nA > nC) std::swap(nA, nC);
            if (nB > nD) std::swap(nB, nD);
            if (nB > nC) std::swap(nB, nC);

            std::array<int, 4> sortedKey{ nA, nB, nC, nD };

            // 4. Access the face pointer
            auto it = faceMap.find(sortedKey);
            if (it != faceMap.end())
            {
                // Store the pointer in this volume's local list
                this->listOfFaces_.push_back(it->second);
            }
            else
            {
                throw std::runtime_error("Accessing a face that was not created before");
            }
        }
    }

    template <int dim, int spacedim>
    std::array<double, spacedim> Volume<dim, spacedim>::interpolate(unsigned int i, unsigned int p)
    {
        unsigned int xIndex = i % (p-1) ;
        unsigned int yIndex = (i / (p-1)) % (p-1) +1;
        unsigned int zIndex = i /((p-1)*(p-1)) +1;

        std::array<double, spacedim> sharedNode = listOfNodes_[0]->getCoordinates();
        std::array<double, spacedim> interpolatedX;
        std::array<double, spacedim> interpolatedY;
        std::array<double, spacedim> interpolatedZ;

        int hit = 0;
        for (const auto& edge : listOfEdges_)
        {
            for (const auto& node : edge->getListOfNodes())
            {
                if (node->getCoordinates() == sharedNode && hit == 0)
                {
                    interpolatedX = edge->interpolate(xIndex, p);
                    hit += 1;
                }
                else if (node->getCoordinates() == sharedNode && hit == 1)
                {
                    interpolatedY = edge->interpolate(yIndex , p);
                    hit += 1;
                }
                else if (node->getCoordinates() == sharedNode && hit == 2)
                {
                    interpolatedZ = edge->interpolate(zIndex, p);
                    hit += 1;
                }
            }
        }


        std::array<double, spacedim> result;

        for (unsigned int d = 0; d < spacedim; ++d)
        {
            result[d] =
                sharedNode[d]
                + (interpolatedX[d] - sharedNode[d])
                + (interpolatedY[d] - sharedNode[d])
                + (interpolatedZ[d] - sharedNode[d]);
        }

        return result;
    }
}

template class Mesh::Volume<1>;
template class Mesh::Volume<2>;
template class Mesh::Volume<3>;
template class Mesh::Volume<1,2>;
template class Mesh::Volume<1,3>;
template class Mesh::Volume<2,3>;