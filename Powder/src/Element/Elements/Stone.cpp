#include "Stone.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Stone::clone() const
{
	return new Stone(*this);
}

Stone::Stone(Simulation& sim)
{
	identifier = EL_STONE;
	name = "Stone";
	description = "Stone";
	colors = { sf::Color(159, 159, 159) };
	color = colors[0];
	mass = 5;
	restitution = 0.f;
	pile_threshold = 1;
	temperature = 295.15f;
	thermal_cond = 1.7f;
	specific_heat_cap = 0.91f;
	endurance = 999;
	state = ST_POWDER;
	high_temperature = 1073.15f;
	high_temperature_transition = EL_LAVA;
	this->sim = &sim;
}

Stone::Stone(const Stone& rhs)
{
	Element::element_copy(rhs);
}


Stone::~Stone()
{
}
