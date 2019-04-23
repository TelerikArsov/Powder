#pragma once
#include "Element/Element.h"
class EXC4 :
	public Element
{
public:
	Element * clone() const override;
	EXC4(Simulation& sim);
	EXC4(const EXC4& rhs);
	~EXC4();
};

