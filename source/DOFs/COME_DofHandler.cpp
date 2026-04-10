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
			for (const auto& elem : mesh_.getElements())
			{
				// loop over all nodes, edges, faces and add the missing volume points
				std::cout << "test" << elem->getTopologicalSupport() << std::endl;
			}
		}
		else
		{
			for (const auto& node : mesh_.getNodes())
			{
				// add the DOFs
			}
			
			for (const auto& edge : mesh_.getEdges())
			{
				// add DOFs based on the number of edges
			}
			if constexpr (dim >= 2)
			{
				for (const auto& face : mesh_.getFaces())
				{
					// add DOFs based on the number of faces
				}

				if constexpr (dim == 3)
				{
					for (const auto& volume : mesh_.getVolumes())
					{
						// add DOFs based on the volume
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