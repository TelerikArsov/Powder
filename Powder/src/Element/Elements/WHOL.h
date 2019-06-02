#pragma once
#include "Element/Element.h"
class WHOL :
	public Element
{
public:
	int update(float dt) override;
	WHOL(Simulation& sim);
	WHOL(const WHOL& rhs);
	~WHOL();
protected:
	Element * clone_impl() const override;
};