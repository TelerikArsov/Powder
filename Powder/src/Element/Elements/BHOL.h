#pragma once
#include "Element/Element.h"
class BHOL :
	public Element
{
public:
	int update(float dt) override;
	void collision_response() override;
	BHOL(Simulation& sim);
	BHOL(const BHOL& rhs);
	~BHOL();
protected:
	Element * clone_impl() const override;
};
