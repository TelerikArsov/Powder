#pragma once
#include "Element/Element.h"
class Metl :
	public Element
{
public:
	Metl(Simulation& sim);
	Metl(const Metl& rhs);
	~Metl();
protected:
	Element * clone_impl() const override;
};