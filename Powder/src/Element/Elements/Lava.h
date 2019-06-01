#pragma once
#include "Element/Element.h"
class Lava :
	public Element
{
public:
	int update(float dt) override;
	Element * clone() const override;
	Lava(Simulation& sim);
	Lava(const Lava& rhs);
	~Lava();
};

