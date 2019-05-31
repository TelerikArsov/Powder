#pragma once
#include "Element/Element.h"
class BHOL :
	public Element
{
public:
	Element * clone() const override;
	BHOL(Simulation& sim);
	BHOL(const BHOL& rhs);
	~BHOL();
};
