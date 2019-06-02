#pragma once
#include "Element/Element.h"
class Gold :
	public Element
{
public:
	Gold(Simulation& sim);
	Gold(const Gold& rhs);
	~Gold();
protected:
	Element * clone_impl() const override;
};