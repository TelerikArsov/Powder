#include "Sand.h"
#include "Simulation.h"
#include "Random.h"

Element* Sand::clone() const
{
	return new Sand(*this);
}

Sand::Sand(Simulation& sim)
{
	identifier = EL_SAND;
	name = "Sand";
	description = "Sand";
	menu_section = 2;
	state = ST_POWDER;
	colors = {sf::Color(237, 201, 175), sf::Color(240, 222, 180)};
	color = colors[random.between(0, colors.size() - 1)];
	mass = 5;
	restitution = 0.1f;
	temperature = 573.15f;
	thermal_cond = 2;
	specific_heat_cap = 0.8f;
	this->sim = &sim;
}

Sand::Sand(const Sand& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	colors = rhs.colors;
	color = colors[random.between(0, colors.size() - 1)];
	drag_coef = rhs.drag_coef;
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	endurance = rhs.endurance;
	x = rhs.x;
	y = rhs.y;
	mass = rhs.mass;
	restitution = rhs.restitution;
	thermal_cond = rhs.thermal_cond;
	specific_heat_cap = rhs.specific_heat_cap;
	temperature = rhs.temperature;
	meltable = rhs.meltable;
	state = rhs.state;
}


Sand::~Sand()
{
}
