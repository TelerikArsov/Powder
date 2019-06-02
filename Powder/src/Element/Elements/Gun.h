#pragma once
#include "Element/Element.h"
class Gun :
	public Element
{
public:
	Gun(Simulation& sim);
	Gun(const Gun& rhs);
	~Gun();
protected:
	Element * clone_impl() const override;
};