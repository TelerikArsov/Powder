#pragma once
#include "Element/Element.h"
class Wtrv :
	public Element
{
public:
	Wtrv(Simulation& sim);
	Wtrv(const Wtrv& rhs);
	~Wtrv();
protected:
	Element * clone_impl() const override;
};