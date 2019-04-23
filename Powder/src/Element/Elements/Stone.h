#pragma once
#include "Element/Element.h"
class Stone :
	public Element
{
public:
	Element* clone() const override;
	Stone(Simulation& sim);
	Stone(const Stone& rhs);
	~Stone();
};

