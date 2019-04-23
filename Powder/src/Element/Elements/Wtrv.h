#pragma once
#include "Element/Element.h"
class Wtrv :
	public Element
{
public:
	Element * clone() const override;
	Wtrv(Simulation& sim);
	Wtrv(const Wtrv& rhs);
	~Wtrv();
};

