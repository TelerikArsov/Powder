#pragma once
#include "GOL.h"
class WALL :
	public GOL
{
public:
	WALL(Simulation& sim);
	WALL(const WALL& rhs);
	~WALL();
protected:
	Element * clone_impl() const override;
};