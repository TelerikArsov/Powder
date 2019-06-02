#pragma once
#include "Element/Element.h"
class Coal :
	public Element
{
public:
	Coal(Simulation& sim);
	Coal(const Coal& rhs);
	~Coal();
protected:
	Element * clone_impl() const override;
};