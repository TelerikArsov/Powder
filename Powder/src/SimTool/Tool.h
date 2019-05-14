#pragma once 
#include <SFML/Graphics.hpp> 
#include <string>
#include "SimObject.h"

class Simulation;

class Tool :
	public SimObject
{ 	
public:
	virtual void do_action(int x, int y, int element_id = -1, Simulation* sim = nullptr, float strength = 0.0f) = 0;
	virtual ~Tool() {};
};