#pragma once
#include "Element/Element.h"
class Lava :
	public Element
{
public:
	Element * clone() const override;
	Lava(Simulation& sim);
	Lava(const Lava& rhs);
	~Lava();
};

