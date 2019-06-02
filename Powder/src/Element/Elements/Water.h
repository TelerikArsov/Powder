#pragma once
#include "Element/Element.h"
class Water :
	public Element
{
public:
	Water(Simulation& sim);
	Water(const Water& rhs);
	~Water();
protected:
	Element * clone_impl() const override;
};