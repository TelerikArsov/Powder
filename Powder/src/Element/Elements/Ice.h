#pragma once
#include "Element/Element.h"
class Ice :
	public Element
{
public:
	Ice(Simulation& sim);
	Ice(const Ice& rhs);
	~Ice();
protected:
	Element * clone_impl() const override;
};