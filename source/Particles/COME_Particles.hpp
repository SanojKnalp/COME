#pragma once
#include "COME_ParticleUtils.hpp"

namespace Particles
{
	template <int dim, int spacedim = dim>
	class Particle
	{
	public:
		Particle() {};

	private:
		Point<dim> location_;
		unsigned int id_;


	};
}