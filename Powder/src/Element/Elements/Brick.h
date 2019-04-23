#pragma once
#include "Element/Element.h"
class Brick :
	public Element
{
public:
	Element * clone() const override;
	Brick(Simulation& sim);
	Brick(const Brick& rhs);
	~Brick();
};

