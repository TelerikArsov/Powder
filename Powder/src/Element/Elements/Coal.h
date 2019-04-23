#pragma once
#include "Element/Element.h"
class Coal :
	public Element
{
public:
	Element * clone() const override;
	Coal(Simulation& sim);
	Coal(const Coal& rhs);
	~Coal();
};

