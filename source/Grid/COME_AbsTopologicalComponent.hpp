#pragma once
#include <iostream>
#include <vector>


// We still need to change the type of lists we have cause i want to use shared pointers, but not sure.
namespace Mesh
{
	class AbsTopologicalComponent
	{
	public:
		unsigned int get_polynomial_degree();

	private:
		unsigned int polynomialDegree_;
		bool isActive_;


	};
}