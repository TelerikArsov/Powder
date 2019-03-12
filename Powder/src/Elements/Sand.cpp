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
	colors = {sf::Color(237, 201, 175), sf::Color(240, 222, 180)};
	color = colors[0];
	mass = 1;
	restitution = 0.1f;
	pile_threshold = 0;
	temperature = 573.15f;
	thermal_cond = 2;
	specific_heat_cap = 0.8f;
	state = ST_POWDER;
	this->sim = &sim;
}

Sand::Sand(const Sand& rhs)
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
}


Sand::~Sand()
{
}
