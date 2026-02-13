#include "COME_Quadrature.hpp"
#include <stdexcept>
namespace Quadrature
{
	template <int dim>
	class QGauss : public Quadrature<dim>
	{
	public:
		virtual double getQuadratureWeight() const;
		virtual double getQuadraturePoint() const;

	private:
		double get_QGauss_weight_degree_1(unsigned int index) const;
		double get_QGauss_weight_degree_2(unsigned int index) const;
		double get_QGauss_weight_degree_3(unsigned int index) const;
		double get_QGauss_weight_degree_4(unsigned int index) const;
		double get_QGauss_weight_degree_5(unsigned int index) const;
		double get_QGauss_weight_degree_6(unsigned int index) const;
		double get_QGauss_weight_degree_7(unsigned int index) const;

	};
}