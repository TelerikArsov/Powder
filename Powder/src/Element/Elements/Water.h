#pragma once
#include "Element/Element.h"
class Water :
	public Element
{
public:
	Element* clone() const override;
	Water(Simulation& sim);
	Water(const Water& rhs);
	~Water();
};

