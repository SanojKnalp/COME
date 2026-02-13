#pragma once
#include <iostream>
#include <vector>
#include "COME_Element.hpp"
namespace Mesh
{
	template <int dim, int spacedim = dim>
	class AbsTopologicalComponent
	{
	public:
		virtual ~AbsTopologicalComponent() = default;

		void activate() { isActive_ = true; };
		void addAdjacentElement(Element<dim, spacedim>* el);
		const std::vector<Element<dim, spacedim>*>& getAdjacentElements() const;

	protected:
		unsigned int polynomialDegree_;
		bool isActive_ = false;
		std::vector<Element<dim,spacedim>*> listOfAdjacentElements_;
	};
}