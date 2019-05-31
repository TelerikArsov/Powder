#pragma once
#include "Element/Element.h"
class WHOL :
	public Element
{
public:
	Element * clone() const override;
	WHOL(Simulation& sim);
	WHOL(const WHOL& rhs);
	~WHOL();
};
