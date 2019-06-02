#pragma once
#include "Element/Element.h"
class Gas :
	public Element
{
public:
	Gas(Simulation& sim);
	Gas(const Gas& rhs);
	~Gas();
protected:
	Element * clone_impl() const override;
};