#pragma once
#include "Element/Element.h"
class BHOL :
	public Element
{
public:
	BHOL(Simulation& sim);
	BHOL(const BHOL& rhs);
	~BHOL();
protected:
	Element * clone_impl() const override;
};
