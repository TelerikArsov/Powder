#pragma once
#include "Element/Element.h"
class Fire :
	public Element
{
public:
	Element * clone() const override;
	virtual int update(float dt) override;
	Fire(Simulation& sim);
	Fire(const Fire& rhs);
	~Fire();
};

