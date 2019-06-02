#pragma once
#include "Element/Element.h"
class Brick :
	public Element
{
public:
	Brick(Simulation& sim);
	Brick(const Brick& rhs);
	~Brick();
protected:
	Element * clone_impl() const override;
};