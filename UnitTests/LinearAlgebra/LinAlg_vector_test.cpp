#include "../catch.hpp"
#include "LinearAlgebra/COME_Linalg_vector.hpp"
#include <cmath>

TEST_CASE("Vector norm test")
{
	using namespace LinearAlgebra;
	Vector<double> b(4);
	b(0) = 1.0;
	b(1) = 0.0;
	b(2) = 2.0;
	b(3) = 2.0;
	REQUIRE(b.norm(2) == Approx(3.0));
}

TEST_CASE("Vector dot product test")
{
	using namespace LinearAlgebra;
	Vector<double> b(3);
	b(0) = 3.0;
	b(1) = 4.0;
	b(2) = 5.0;
	Vector<double> c = b;
	double dotval = c.dot(b);
	REQUIRE(dotval == Approx(50.0));
}

TEST_CASE("Vector row removal test")
{
	using namespace LinearAlgebra;
	Vector<double> b(3);
	b(0) = 3.0;
	b(1) = 4.0;
	b(2) = 5.0;
	Vector<double> c = b.removeRow(1);;
	REQUIRE(c.size() == 2);
}

TEST_CASE("Vector reinit")
{
	using namespace LinearAlgebra;
	Vector<float> A;
	REQUIRE(A.size() == 0);
	A.reinit(5);
	REQUIRE(A.size() == 5);
}