#pragma once
#include "Element/Element.h"
class Oil :
	public Element
{
public:
	Element * clone() const override;
	Oil(Simulation& sim);
	Oil(const Oil& rhs);
	~Oil();
};



