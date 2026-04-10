#include "COME_DofHandler.hpp"

namespace DOFs
{
	unsigned int getId() const
	{
		return ID_;
	}

	std::array<double, spacedim>& getCoordinates() const
	{
		return coordinates_;
	}
}