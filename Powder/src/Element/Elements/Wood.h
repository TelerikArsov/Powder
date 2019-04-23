#pragma once
#include "Element/Element.h"
class Wood :
	public Element
{
public:
	Element * clone() const override;
	Wood(Simulation& sim);
	Wood(const Wood& rhs);
	~Wood();
};

