#pragma once
#include "Element/Element.h"
class Acid :
	public Element
{
public:
	Acid(Simulation& sim);
	Acid(const Acid& rhs);
	~Acid();
protected:
	Element* clone_impl() const override;
};

