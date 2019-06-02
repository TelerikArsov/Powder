#pragma once
#include "Element/Element.h"
class Fire :
	public Element
{
public:
	Fire(Simulation& sim);
	Fire(const Fire& rhs);
	~Fire();
protected:
	Element * clone_impl() const override;
};