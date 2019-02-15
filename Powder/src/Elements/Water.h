#pragma once
#include "Element.h"
class Water :
	public Element
{
public:
	bool update(double dt);
	Element* clone() const override;
	Water(Simulation& sim);
	Water(const Water& rhs);
	~Water();
};

