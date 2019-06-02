#pragma once
#include "Element/Element.h"
class Wood :
	public Element
{
public:
	Wood(Simulation& sim);
	Wood(const Wood& rhs);
	~Wood();
protected:
	Element * clone_impl() const override;
};