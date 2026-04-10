#pragma once
#include "Grid/COME_Mesh.hpp"
#include "FEM/ShapeFunctions/COME_ShapeFunctions.hpp"
#include "COME_DofUtils.hpp"

#include <vector>
#include <memory>

namespace DOFs
{
	template <int dim, int spacedim = dim>
	class DoFHandler
	{
	public:
		DoFHandler(Mesh::Mesh<dim, spacedim>& mesh) : mesh_(mesh) {}

		void distribute_dofs(const ShapeFunctions::ShapeFunctions<dim, spacedim>& fe);

		unsigned int number_of_dofs() const;
	private:
		Mesh::Mesh<dim, spacedim>& mesh_;
		std::vector<std::unique_ptr<DOF<dim, spacedim>>> DoFList_;


	};
	
}