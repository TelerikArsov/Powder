#pragma once
#include "Element/Element.h"
class Lava :
	public Element
{
public:
	int update(float dt) override;
	Lava(Simulation& sim);
	Lava(const Lava& rhs);
	~Lava();
protected:
	Element * clone_impl() const override;
};