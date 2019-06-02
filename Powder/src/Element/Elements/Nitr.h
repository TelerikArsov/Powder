#pragma once
#include "Element/Element.h"
class Nitr :
	public Element
{
public:
	Nitr(Simulation& sim);
	Nitr(const Nitr& rhs);
	~Nitr();
protected:
	Element * clone_impl() const override;
};