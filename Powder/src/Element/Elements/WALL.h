#pragma once
#include "GOL.h"
class WALL :
	public GOL
{
public:
	Element * clone() const override;
	WALL(Simulation& sim);
	WALL(const WALL& rhs);
	~WALL();
};

