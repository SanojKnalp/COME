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
	template<int dim,int spacedim>
	void Mesh<dim,spacedim>::addEdge()
	{

	}
	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::addNode(int index, const std::array<double, spacedim>& positions)
	{
		listOfNodes_.emplace_back(std::make_unique<Node<dim, spacedim>>(index, positions));
		nodeIdMap_[id] = listOfNodes_.back().get();
	}
	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::addFace()
	{

	}
	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::addElement(int elementnumber, const std::array<int, 1 << spacedim>& nodes)
	{

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
			if (section == 1)						
			{
				std::array<double, spacedim> position;
				for (int i = 0; i < spacedim; i++)
				{
					position[i] = std::stod(fields[i + 1]);		//convert all positions from strings to integers
				}
				this->addNode(std::stoi(fields[0]),position);
			}
			if (section == 2)
			{
				std::array<int, 1 << spacedim> nodes;			
				for (int i = 0; i < std::pow(2, spacedim); i++)
				{
					nodes[i] = std::stoi(fields[i + 1]);		//store all the node indices that belong to that one element
				}
				this->addElement(std::stoi(fields[0]), nodes);
			}

		}

		std::cout << "Size of node_vector:" << listOfNodes_.size() << std::endl;


	}

	template<int dim, int spacedim>
	void Mesh<dim, spacedim>::read_msh(std::istream& in)
	{

	}

}

template class Mesh::Mesh<1>;
template class Mesh::Mesh<2>;
template class Mesh::Mesh<3>;
template class Mesh::Mesh<1, 2>;
template class Mesh::Mesh<1, 3>;
template class Mesh::Mesh<2, 3>;