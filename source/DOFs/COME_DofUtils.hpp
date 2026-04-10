#pragma once
#include <array>


namespace DOFs
{
	template <int dim, int spacedim = dim>
	class DOF
	{
	public:
		DOF(const std::array<double, spacedim>& coordinates, unsigned int ID)
			: coordinates_(coordinates), ID_(ID) 
		{}

		unsigned int getId() const;
		std::array<double, spacedim>& getCoordinates() const;

	private:
		std::array<double, spacedim> coordinates_;
		unsigned int ID_;
		unsigned int ElementId_;
	};
}