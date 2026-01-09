
/* this is kinda how we are going to implement our base CoordinateSystem class. Polymorphism let's gooooo*/

//This class needs to be reworked after we have the mesh class in place such that we can place Nodes as an important simplification as our christoffelsymbols depend on the radius

namespace CoordinateSystem
{
	class CoordinateSystem
	{
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value);
	};

	class CartesianCoordinates : public CoordinateSystem
	{
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value);
	};

	class CylindricalCoordinates : public CoordinateSystem
	{
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value);
	};

	class SphericalCoordinates : public CoordinateSystem
	{
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value);
	};




	double CartesianCoordinates::get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value)
	{
		return 0.0;
	}

	double CylindricalCoordinates::get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double r)
	{
		if (i == 1 && j == 2 && k == 2) {
			return -r;
		}

		if (i == 2 && j == 1 && k == 2) {
			return 1.0 / r;
		}

		if (i == 2 && j == 2 && k == 1) {
			return 1.0 / r;
		}

		return 0.0;
	}

	double SphericalCoordinates::get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double r)
	{

	}
}