#pragma once
#include "Element/Element.h"
class Fire :
	public Element
{
public:
	Element * clone() const override;
	Fire(Simulation& sim);
	Fire(const Fire& rhs);
	~Fire();
};

