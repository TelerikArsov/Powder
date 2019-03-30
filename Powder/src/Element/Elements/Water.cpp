#include "Water.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Water::clone() const
{
	return new Water(*this);
}

Water::Water(Simulation& sim)
{
	identifier = EL_WATER;
	name = "Water";
	description = "Water";
	colors = {sf::Color::Blue};
	color = colors[0];
	mass = 1;
	restitution = 0.0f;
	temperature = 293.15f;
	thermal_cond = 0.606f;
	specific_heat_cap = 4.19f;
	state = ST_LIQUID;
	low_temperature = 273.15f;
	low_temperature_transition = EL_ICE;
	//high_temperature = FLT_MAX;
	//high_temperature_transition = -1;
	this->sim = &sim;
}

Water::Water(const Water& rhs)
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
	low_temperature = rhs.low_temperature;
	low_temperature_transition = rhs.low_temperature_transition;
	//high_temperature = FLT_MAX;
	//high_temperature_transition = -1;
}


Water::~Water()
{
}
