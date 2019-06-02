#include "Brick.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Brick::clone_impl() const
{
	return new Brick(*this);
}

Brick::Brick(Simulation& sim)
{
	identifier = EL_BRICK;
	name = "Brick";
	description = "Brick";
	colors = { sf::Color(203, 65, 84) };
	color = colors[0];
	mass = 5;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 1.31f;
	specific_heat_cap = 1.f;
	endurance = 999;
	state = ST_SOLID;
	prop = Red_Glow;
	high_pressure = 8.8f;
	high_pressure_transition = EL_STONE;
	high_temperature = 1223.15f;
	high_temperature_transition = EL_LAVA;

	this->sim = &sim;
}

Brick::Brick(const Brick& rhs)
{
	Element::element_copy(rhs);
}


Brick::~Brick()
{
}
