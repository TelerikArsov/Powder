#pragma once
#include "Element/Element.h"
class Nitr :
	public Element
{
public:
	Element * clone() const override;
	Nitr(Simulation& sim);
	Nitr(const Nitr& rhs);
	~Nitr();
};

