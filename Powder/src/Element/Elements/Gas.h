#pragma once
#include "Element/Element.h"
class Gas :
	public Element
{
public:
	Element * clone() const override;
	Gas(Simulation& sim);
	Gas(const Gas& rhs);
	~Gas();
};

