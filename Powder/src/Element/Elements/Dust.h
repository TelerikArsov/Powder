#pragma once
#include "Element/Element.h"
class Dust :
	public Element
{
public:
	Dust(Simulation& sim);
	Dust(const Dust& rhs);
	~Dust();
protected:
	Element * clone_impl() const override;
};