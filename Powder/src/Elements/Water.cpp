#include "Water.h"
#include "Simulation.h"
#include "Random.h"

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
	temperature = 22;
	thermal_cond = 0.606f;
	specific_heat_cap = 4.19f;
	state = ST_LIQUID;
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
}


Water::~Water()
{
}
