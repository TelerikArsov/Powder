#pragma once
#include "Element/Element.h"
class Acid :
	public Element
{
public:
	Element * clone() const override;
	Acid(Simulation& sim);
	Acid(const Acid& rhs);
	~Acid();
};

