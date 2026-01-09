#pragma once
#include <istream>


namespace Grid
{
	template <int dim, int spacedim = dim>
	class GridIn
	{
	public:
		enum Format
		{
			abaqus,
			msh,
		};
		//Default Constructor
		GridIn() = default;

		void read_abaqus(std::istream& in);
		void read_msh(std::istream& in);

	private:

	};
}
