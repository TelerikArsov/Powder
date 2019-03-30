#pragma once
#include "Element/Element.h"
class Ice :
	public Element
{
public:
	Element * clone() const override;
	Ice(Simulation& sim);
	Ice(const Ice& rhs);
	~Ice();
};

