#pragma once
#include "Element/Element.h"
class Stone :
	public Element
{
public:
	Stone(Simulation& sim);
	Stone(const Stone& rhs);
	~Stone();
protected:
	Element * clone_impl() const override;
};