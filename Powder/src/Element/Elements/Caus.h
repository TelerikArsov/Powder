#pragma once
#include "Element/Element.h"
class Caus :
	public Element
{
public:
	Element * clone() const override;
	Caus(Simulation& sim);
	Caus(const Caus& rhs);
	~Caus();
};

