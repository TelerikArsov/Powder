#pragma once
#include "Element/Element.h"
class EXC4 :
	public Element
{
public:
	EXC4(Simulation& sim);
	EXC4(const EXC4& rhs);
	~EXC4();
protected:
	Element * clone_impl() const override;
};