#pragma once
#include "Element/Element.h"
class Oil :
	public Element
{
public:
	Oil(Simulation& sim);
	Oil(const Oil& rhs);
	~Oil();
protected:
	Element* clone_impl() const override;
};