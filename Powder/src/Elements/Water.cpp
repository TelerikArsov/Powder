#include "Water.h"
#include "Simulation.h"

Element* Water::clone() const
{
	return new Water(*this);
}

Water::Water(Simulation& sim)
{
	identifier = EL_WATER;
	name = "Water";
	description = "Water";
	menu_section = 2;
	state = ST_LIQUID;
	color = sf::Color::Blue;
	mass = 1;
	restitution = 0.6;
	temperature = 22;
	thermal_cond = 0.606;
	specific_heat_cap = 4.19;
	this->sim = &sim;
	//calc_term_vel();
}

Water::Water(const Water& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	color = rhs.color;
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


Water::~Water()
{
}
