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
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	colors = rhs.colors;
	color = colors[random.between(0, colors.size() - 1)];
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	set_pos(rhs.x, rhs.y, true);
	drag_coef = rhs.drag_coef;
	mass = rhs.mass;
	endurance = rhs.endurance;
	restitution = rhs.restitution;
	pile_threshold = rhs.pile_threshold;
	temperature = rhs.temperature;
	thermal_cond = rhs.thermal_cond;
	specific_heat_cap = rhs.specific_heat_cap;
	meltable = rhs.meltable;
	state = rhs.state;
	high_temperature = rhs.high_temperature;
	high_temperature_transition = rhs.high_temperature_transition;
}


Ice::~Ice()
{
}
