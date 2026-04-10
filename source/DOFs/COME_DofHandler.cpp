#include "COME_DofHandler.hpp"

namespace DOFs
{
	template <int dim, int spacedim>
	void DoFHandler<dim, spacedim>::distribute_dofs(const ShapeFunctions::ShapeFunctions<dim, spacedim>& fe)
	{
		// the approach here is based on continuity
		// if it's discontinuous, we loop over all the elements and then loop over all the local nodes, edges, faces and the volume itself and with that add the DOFs. 
		// if it's continuous, we loop over the global nodes, then the edges, then faces, then volumes and add on each level the respecitive nodes.
		// This way we don't produce duplicates for continuous elements and actually duplicate for discontinuous elements.
		if (fe.isDiscontinuous())
		{
			/*unsigned int next_dof = 0;
			unsigned int p = fe.getPolynomialDegree();
			unsigned int n_local_dofs = std::pow(p + 1, dim);
			for (const auto& elem : mesh_.getElements())
			{
				for (unsigned int i = 0; i < n_local_dofs; ++i)
				{
					auto coord = elem->interpolate_tensor_product(i, p);

					elem->getTopologicalSupport()->add_dof(next_dof);
					DoFList_.push_back(std::make_unique<DOF<dim, spacedim>>(coord, next_dof));
					++next_dof;
				}
			}*/
		}
		else
		{
			unsigned int next_dof = 1;
			unsigned int p = fe.getPolynomialDegree();
			unsigned int edge_dofs = (p >= 2) ? (p - 1) : 0;

			// 1. vertices
			for (auto& node : mesh_.getNodes())
			{
				node->add_dof(next_dof);
				DoFList_.push_back(std::make_unique<DOF<dim, spacedim>>(node->getCoordinates(), next_dof));
				next_dof += 1;
			}

			// 2. edges
			if (edge_dofs > 0)
			{
				for (auto& edge : mesh_.getEdges())
				{
					for (unsigned int i = 0; i < edge_dofs; ++i)
					{
						auto coord = edge->interpolate(i + 1, p);

						edge->add_dof(next_dof);
						DoFList_.push_back(std::make_unique<DOF<dim, spacedim>>(coord, next_dof));
						next_dof += 1;
					}
				}
			}

			// 3. faces (2D/3D)
			if constexpr (dim >= 2)
			{
				unsigned int face_dofs = (p >= 2) ? (p - 1) * (p - 1) : 0;

				for (auto& face : mesh_.getFaces())
				{
					for (unsigned int i = 0; i < face_dofs; ++i)
					{
						auto coord = face->interpolate(i, p);

						face->add_dof(next_dof);
						DoFList_.push_back(std::make_unique<DOF<dim, spacedim>>(coord, next_dof));
						next_dof += 1;
					}
				}
			}

			if constexpr (dim == 3)
			{
				unsigned int volume_dofs = (p >= 2) ? (p - 1) * (p - 1) * (p - 1) : 0;
				for (auto& volume : mesh_.getVolumes())
				{
					for (unsigned int i = 0; i < volume_dofs; i++)
					{
						auto coord = volume->interpolate(i, p);
						volume->add_dof(next_dof);
						DoFList_.push_back(std::make_unique<DOF<dim, spacedim>>(coord, next_dof));
						next_dof += 1;
					}
				}
			}
			
		}

		
	}

	template <int dim, int spacedim>
	unsigned int DoFHandler<dim, spacedim>::number_of_dofs() const
	{
		return DoFList_.size();
	}
}
template class DOFs::DoFHandler<1>;
template class DOFs::DoFHandler<2>;
template class DOFs::DoFHandler<3>;
template class DOFs::DoFHandler<1,2>;
template class DOFs::DoFHandler<1,3>;
template class DOFs::DoFHandler<2,3>;