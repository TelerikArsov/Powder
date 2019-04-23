#pragma once
#include "Element/Element.h"
class Gun :
	public Element
{
public:
	Element * clone() const override;
	Gun(Simulation& sim);
	Gun(const Gun& rhs);
	~Gun();
};

