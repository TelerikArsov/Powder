#pragma once
#include "Element/Element.h"
class Gold :
	public Element
{
public:
	Element * clone() const override;
	Gold(Simulation& sim);
	Gold(const Gold& rhs);
	~Gold();
};

