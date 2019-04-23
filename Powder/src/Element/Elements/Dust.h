#pragma once
#include "Element/Element.h"
class Dust :
	public Element
{
public:
	Element * clone() const override;
	Dust(Simulation& sim);
	Dust(const Dust& rhs);
	~Dust();
};

