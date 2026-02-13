#include <cmath>
//This class needs to be reworked after we have the mesh class in place such that we can place Nodes as an important simplification as our christoffelsymbols depend on the radius
namespace CoordinateSystem
{
	class CoordinateSystem
	{
	public:
		CoordinateSystem() = default;
		virtual ~CoordinateSystem() = default;
		virtual double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value) const = 0;
	};

	class CartesianCoordinates : public CoordinateSystem
	{
	public:
		CartesianCoordinates() : CoordinateSystem() {}
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value) const;
	};

	class CylindricalCoordinates : public CoordinateSystem 
	{
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value) const;
	};

	class SphericalCoordinates : public CoordinateSystem
	{
		double get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double r, double theta);
	};


	double CartesianCoordinates::get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double value) const
	{
		return 0.0;
	}

	double CylindricalCoordinates::get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double r) const
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

	double SphericalCoordinates::get_Christoffel_symbol(unsigned int i, unsigned int j, unsigned int k, double r, double theta)
	{
		if (i == 1 && j == 2 && k == 2)
		{
			return -r;
		}

		if (i == 1 && j == 3 && k == 3)
		{
			return -r*std::sin(theta)*std::sin(theta);
		}

		if (i == 2 && j == 1 && k == 2) {
			return 1.0 / r;
		}

		if (i == 2 && j == 2 && k == 1) {
			return 1.0 / r;
		}

		if (i == 2 && j == 3 && k == 3)
		{
			return -std::sin(theta) * std::cos(theta);
		}

		if (i == 3 && j == 1 && k == 3)
		{
			return 1.0 / r;
		}

		if (i == 3 && j == 3 && k == 1)
		{
			return 1.0 / r;
		}

		if (i == 3 && j == 2 && k == 3)
		{
			return std::cos(theta) / std::sin(theta);
		}

		if (i == 3 && j == 3 && k == 2)
		{
			return std::cos(theta) / std::sin(theta);
		}
		
		
		return 0.0;
	}
}


