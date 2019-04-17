#include "Ice.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Ice::clone() const
{
	return new Ice(*this);
}

Ice::Ice(Simulation& sim)
{
	identifier = EL_ICE;
	name = "Ice";
	description = "Ice Ice baby";
	colors = { sf::Color(159, 191, 254) };
	color = colors[0];
	mass = 1;
	restitution = 0.1f;
	pile_threshold = 0;
	temperature = 245.15f;
	thermal_cond = 2.18f;
	specific_heat_cap = 0.50f;
	state = ST_SOLID;
	this->sim = &sim;
	high_temperature = 273.15f;
	high_temperature_transition = EL_WATER;
}

Ice::Ice(const Ice & rhs)
{
	Element::element_copy(rhs);
	color = colors[random.between(0, colors.size() - 1)];
}


Ice::~Ice()
{
}
