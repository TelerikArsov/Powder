#pragma once
#include "Element/Element.h"
class Sand :
	public Element
{
public:
	Sand(Simulation& sim);
	Sand(const Sand& rhs);
	~Sand();
protected:
	Element * clone_impl() const override;
};