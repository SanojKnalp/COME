#pragma once
#include "COME_Node.hpp"
#include "COME_Edge.hpp"
#include "COME_Element.hpp"
#include "COME_Face.hpp"
#include "COME_Volume.hpp"
#include "Grid/COME_AbsTopologicalComponent.hpp"
#include "FEM/FEValues/COME_FEValues.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <sstream>
#include <array>
#include <unordered_map>
#include <map>
#include <algorithm>

namespace Mesh
{
	template <int dim, int spacedim = dim>
	class Mesh
	{

	public:
		enum Format
		{
			abaqus,
			gmsh,
		};
		Mesh() = default;
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		void addEdge(const std::array<int,1 << dim>& nodes);
		void addNode(int nodeindex,const std::array<double,spacedim>& positions);
		void addFace(const std::array<int, 1 << dim>& nodes);
		void addElement(int elementnumber, const std::array<int, 1 << dim>& nodes);

		void addEdgeIfMissing(int nodeA, int nodeB);
		void addFaceIfMissing(int nodeA, int nodeB, int nodeC, int nodeD);

		void read_abaqus(std::istream& in);
		void read_msh(std::istream& in);

		const std::unordered_map<int, Node<dim, spacedim>*>& getNodeMap() const;
		const std::vector<std::unique_ptr<Node<dim, spacedim>>>& getNodes() const;
		const std::vector<std::unique_ptr<Edge<dim, spacedim>>>& getEdges() const;
		const std::vector<std::unique_ptr<Face<dim, spacedim>>>& getFaces() const;
		const std::vector<std::unique_ptr<Volume<dim, spacedim>>>& getVolumes() const;
		const std::vector<std::unique_ptr<Element<dim, spacedim>>>& getElements() const;

	private:
		std::vector<std::unique_ptr<Edge<dim,spacedim>>>		listOfEdges_;
		std::vector<std::unique_ptr<Element<dim,spacedim>>>		listOfElements_;
		std::vector<std::unique_ptr<Face<dim,spacedim>>>		listOfFaces_;
		std::vector<std::unique_ptr<Node<dim,spacedim>>>		listOfNodes_;
		std::vector<std::unique_ptr<Volume<dim, spacedim>>>		listOfVolumes_;

		std::vector<std::string> split_csv(const std::string& line) const;
		
		std::unordered_map<int, Node<dim, spacedim>*> nodeIdMap_;
		std::map<std::pair<int, int>, Edge<dim, spacedim>*> edgeMap_; //smart way of storing an Edge pointer with a node mapping.
		std::map<std::array<int, 4>, Face<dim, spacedim>*> faceMap_;


		enum AbaqusMeshSection {
			NONE,
			NODE,
			ELEMENT
		};
		
		
	};
}