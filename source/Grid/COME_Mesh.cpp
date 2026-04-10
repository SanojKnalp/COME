#include "COME_Mesh.hpp"

namespace Mesh
{

	template<int dim, int spacedim>
	std::vector<std::string> Mesh<dim,spacedim>::split_csv(const std::string& line) const{
		std::vector<std::string> tokens;
		std::stringstream ss(line);		//extract values from the line
		std::string token;				

		while (std::getline(ss, token, ',')) {
			token.erase(0, token.find_first_not_of(" \t"));			//remove all leading whitespaces
			token.erase(token.find_last_not_of(" \t") + 1);			//remove all trailing whitespaces
			tokens.push_back(token);								
		}
		return tokens;
	}

	template <int dim, int spacedim>
	void Mesh<dim, spacedim>::addEdgeIfMissing(int nodeA, int nodeB)
	{
		auto [minNode, maxNode] = std::minmax(nodeA, nodeB);
		std::pair key{ minNode, maxNode };

		auto [it, inserted] = edgeMap_.try_emplace(key, nullptr);
		if (inserted)
		{
			listOfEdges_.emplace_back(std::make_unique<Edge<dim, spacedim>>());
			listOfEdges_.back()->linkNodes(std::array{ minNode,maxNode }, nodeIdMap_);
		}
	}
	template <int dim, int spacedim>
	void Mesh<dim, spacedim>::addFaceIfMissing(int nodeA, int nodeB, int nodeC, int nodeD)
	{
		// 1. Keep the original order for connectivity
		std::array<int, 4> connectivity{ nodeA, nodeB, nodeC, nodeD };

		// 2. Create a sorted version for the Map Key
		if (nodeA > nodeB) std::swap(nodeA, nodeB);
		if (nodeC > nodeD) std::swap(nodeC, nodeD);
		if (nodeA > nodeC) std::swap(nodeA, nodeC);
		if (nodeB > nodeD) std::swap(nodeB, nodeD);
		if (nodeB > nodeC) std::swap(nodeB, nodeC);

		std::array<int, 4> key{ nodeA, nodeB, nodeC, nodeD };

		auto [it, inserted] = faceMap_.try_emplace(key, nullptr);

		if (inserted)
		{
			auto newFace = std::make_unique<Face<dim, spacedim>>();

			// Link nodes using original order so the face knows its shape
			newFace->linkNodes(connectivity, nodeIdMap_);

			// Link edges using original order so it finds (A,B), (B,C), etc.
			newFace->linkEdges(connectivity, edgeMap_);

			it->second = newFace.get(); // Don't forget to update the map pointer!
			listOfFaces_.push_back(std::move(newFace));
		}

	}

	template<int dim,int spacedim>
	void Mesh<dim, spacedim>::addEdge(const std::array<int,1 << dim>& nodes)
	{
		addEdgeIfMissing(nodes[0], nodes[1]);
		addEdgeIfMissing(nodes[1], nodes[2]);
		addEdgeIfMissing(nodes[2], nodes[3]);
		addEdgeIfMissing(nodes[0], nodes[3]);
		if constexpr (dim == 3)
		{
			addEdgeIfMissing(nodes[0], nodes[4]);
			addEdgeIfMissing(nodes[1], nodes[5]);
			addEdgeIfMissing(nodes[2], nodes[6]);
			addEdgeIfMissing(nodes[3], nodes[7]);
			addEdgeIfMissing(nodes[4], nodes[5]);
			addEdgeIfMissing(nodes[5], nodes[6]);
			addEdgeIfMissing(nodes[6], nodes[7]);
			addEdgeIfMissing(nodes[4], nodes[7]);
		}

	}

	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::addNode(int index, const std::array<double, spacedim>& positions)
	{
		listOfNodes_.emplace_back(std::make_unique<Node<dim, spacedim>>(index, positions));
		nodeIdMap_[index] = listOfNodes_.back().get();
	}
	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::addFace(const std::array<int, 1 << dim>& nodes)
	{
		// Correct Perimeter Winding (Counter-Clockwise/Clockwise, but NOT crossing diagonals)
		addFaceIfMissing(nodes[0], nodes[1], nodes[2], nodes[3]); // Bottom
		addFaceIfMissing(nodes[4], nodes[5], nodes[6], nodes[7]); // Top
		addFaceIfMissing(nodes[0], nodes[1], nodes[5], nodes[4]); // Front (was 0,1,4,5)
		addFaceIfMissing(nodes[1], nodes[2], nodes[6], nodes[5]); // Right (was 1,2,5,6)
		addFaceIfMissing(nodes[2], nodes[3], nodes[7], nodes[6]); // Back  (was 2,3,6,7)
		addFaceIfMissing(nodes[3], nodes[0], nodes[4], nodes[7]); // Left  (was 0,3,4,7)

	}

    template<int dim, int spacedim>
    void Mesh<dim, spacedim>::addElement(int elementnumber, const std::array<int, 1 << dim>& nodes)
    {
        //First, we create an Element
        auto element = std::make_unique<Element<dim, spacedim>>();
        Element<dim, spacedim>* elPtr = element.get();

        //Next, we create the highest possible topological support we can and link it to our element
        if constexpr (dim == 1) {
            auto edge = std::make_unique<Edge<dim, spacedim>>();
			Edge<dim, spacedim>* edgePtr = edge.get();
            elPtr->setTopologicalSupport(edgePtr);
            listOfEdges_.push_back(std::move(edge));
        }
        else if constexpr (dim == 2) {
            auto face = std::make_unique<Face<dim, spacedim>>();
			Face<dim, spacedim>* facePtr = face.get();
            elPtr->setTopologicalSupport(facePtr);
            listOfFaces_.push_back(std::move(face));
        }
        else if constexpr (dim == 3) {
            auto volume = std::make_unique<Volume<dim, spacedim>>();
			Volume<dim, spacedim>* volPtr = volume.get();
            elPtr->setTopologicalSupport(volPtr);
            listOfVolumes_.push_back(std::move(volume));
        }
		// Here we create our edges (if we are higher than dim 1)
		if constexpr (dim == 2)
		{
			addEdge(nodes);
		}
		else if constexpr (dim == 3)
		{
			//here, we need to create and set the edges with respect to the correct numbering
			//Strategy here: Extract all the different node pairs and then throw them into addEdge()
			//There we check if we have the edge already or not.
			//Important for edges: Sort. Smaller number first to make life easier. But we do that in addEdge

			addEdge(nodes); //fill with correct indices->current issue. How do we link volume and edges????
		}
		//Here we create our Faces. We don't need it for dim == 2 because we already created our face.
		if constexpr (dim == 3)
		{
			//same thing here again for faces. Very simple indeed. Again sort 
			addFace(nodes);
		}

		//Here we link our nodes
		//Here we use a little trick that because we only access the dim we can immediately link the correct element
		if constexpr (dim == 1)
		{
			listOfEdges_.back()->linkNodes(nodes, nodeIdMap_);
		}
		else if constexpr (dim == 2)
		{
			listOfFaces_.back()->linkNodes(nodes, nodeIdMap_);
			listOfFaces_.back()->linkEdges(nodes, edgeMap_);
		}
		else if constexpr (dim == 3)
		{
			listOfVolumes_.back()->linkNodes(nodes, nodeIdMap_);
			listOfVolumes_.back()->linkEdges(nodes, edgeMap_);
			listOfVolumes_.back()->linkFaces(nodes, faceMap_);
		}


		listOfElements_.push_back(std::move(element));

        
    }


	/*
	Generally for all read_mesh functions, we make the following assumption:
	The DOFs are filled from x to z. So e.g. when we have a 2d mesh, we have x and y and not x and z.
	This makes my life significantly easier cause i don't need to make sure i account for all the different directions my mesh could possibly be oriented towards.
	It also makes sense cause one can always rotate the mesh properly
	We also for right now assume that we don't need to do line skips and stuff like that, so i guess we start with very basic meshes for now.
	*/
	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::read_abaqus(std::istream& in)
	{
		
		if (!in) {
			std::cerr << "File could not be opened. Current directory: "
				<< std::filesystem::current_path() << "\n";
			throw std::runtime_error("File could not be opened");
		}


		std::string line;

		AbaqusMeshSection section = AbaqusMeshSection::NONE;
		//Loop through all lines
		while (std::getline(in, line)) {
			
			if (line.empty()) continue; //ignore empty lines

			if (line[0] == '*') {						//now if we actually hit a new type, we need to change the respective type we read in
				if (line.find("*NODE") == 0) {
					section = AbaqusMeshSection::NODE;
					
				}
				else if (line.find("*ELEMENT") == 0) {
					section = AbaqusMeshSection::ELEMENT;
				}
				else {
					section = AbaqusMeshSection::NONE;
				}
				continue;
			}

			auto fields = split_csv(line);			//split the line

			//If we are reading in a Node
			if (section == AbaqusMeshSection::NODE)
			{
				std::array<double, spacedim> position;
				for (int i = 0; i < spacedim; i++)
				{
					position[i] = std::stod(fields[i + 1]);		//convert all positions from strings to integers
				}
				this->addNode(std::stoi(fields[0]),position);
			}
			if (section == AbaqusMeshSection::ELEMENT)
			{
				std::array<int, 1 << dim> nodes;			
				for (int i = 0; i < (1 << dim); i++)
				{
					nodes[i] = std::stoi(fields[i + 1]);		//store all the node indices that belong to that one element
				}
				this->addElement(std::stoi(fields[0]), nodes);
			}

		}
	}

	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::read_msh(std::istream& in)
	{

	}

	template<int dim, int spacedim>
	const std::unordered_map<int, Node<dim, spacedim>*>& Mesh<dim, spacedim>::getNodeMap() const
	{
		return nodeIdMap_;
	}

	template <int dim, int spacedim>
	const std::vector<std::unique_ptr<Node<dim, spacedim>>>& Mesh<dim, spacedim>::getNodes() const
	{
		return listOfNodes_;
	}

	template <int dim, int spacedim>
	const std::vector<std::unique_ptr<Edge<dim, spacedim>>>& Mesh<dim, spacedim>::getEdges() const
	{
		return listOfEdges_;
	}

	template <int dim, int spacedim>
	const std::vector<std::unique_ptr<Face<dim, spacedim>>>& Mesh<dim, spacedim>::getFaces() const
	{
		return listOfFaces_;
	}

	template <int dim, int spacedim>
	const std::vector<std::unique_ptr<Volume<dim, spacedim>>>& Mesh<dim, spacedim>::getVolumes() const
	{
		return listOfVolumes_;
	}

	template <int dim, int spacedim>
	const std::vector<std::unique_ptr<Element<dim, spacedim>>>& Mesh<dim,spacedim>::getElements() const
	{
		return listOfElements_;
	}

}

template class Mesh::Mesh<1>;
template class Mesh::Mesh<2>;
template class Mesh::Mesh<3>;
template class Mesh::Mesh<1, 2>;
template class Mesh::Mesh<1, 3>;
template class Mesh::Mesh<2, 3>;