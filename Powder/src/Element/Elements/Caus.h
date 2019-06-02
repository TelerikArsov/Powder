#pragma once
#include "Element/Element.h"
class Caus :
	public Element
{
public:
	Caus(Simulation& sim);
	Caus(const Caus& rhs);
	~Caus();
protected:
	Element * clone_impl() const override;
};

