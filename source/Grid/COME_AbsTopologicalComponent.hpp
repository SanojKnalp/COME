#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stdexcept>


namespace Mesh
{
	template <int dim, int spacedim>
	class Element;

	template <int dim, int spacedim = dim>
	class AbsTopologicalComponent
	{
	public:
		virtual ~AbsTopologicalComponent() = default;

		void activate() { isActive_ = true; };
		void addAdjacentElement(Element<dim, spacedim>* el);
		const std::vector<Element<dim, spacedim>*>& getAdjacentElements() const;

	protected:
		unsigned int polynomialDegree_ = 1;
		bool isActive_ = false;
		std::vector<Element<dim,spacedim>*> listOfAdjacentElements_;
		unsigned int refinementLevel_ = 0;

	};

	template<int dim, int spacedim>
	void AbsTopologicalComponent<dim, spacedim>::addAdjacentElement(Element<dim, spacedim>* el)
	{
		listOfAdjacentElements_.push_back(el);
	}
	template<int dim, int spacedim>
	const std::vector<Element<dim, spacedim>*>& AbsTopologicalComponent<dim, spacedim>::getAdjacentElements() const
	{
		return listOfAdjacentElements_;
	}

}