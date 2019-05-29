#pragma once
#include "Element/Element.h"
class Metl :
	public Element
{
public:
	Element * clone() const override;
	Metl(Simulation& sim);
	Metl(const Metl& rhs);
	~Metl();
};
