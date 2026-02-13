namespace Quadrature
{
	template<int dim>
	class Quadrature
	{
	public:
		Quadrature(int order) 
			: quadOrder_(order) {};
		int getQuadratureOrder() const;
		virtual double  getQuadratureWeight() const = 0;
		virtual double getQuadraturePoint() const = 0;

	protected:
		int quadOrder_;
	};

	template<int dim>
	int Quadrature<dim>::getQuadratureOrder() const
	{
		return quadOrder_;
	}



}