#include "Metl.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Metl::clone_impl() const
{
	return new Metl(*this);
}

Metl::Metl(Simulation& sim)
{
	identifier = EL_METL;
	name = "Metl";
	description = "Metl";
	colors = { sf::Color(63, 63, 95) };
	color = colors[0];
	mass = 5;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 94.f;
	specific_heat_cap = 0.45f;
	endurance = 999;
	state = ST_SOLID;
	prop = Red_Glow;
	high_temperature = 1237;
	high_temperature_transition = EL_LAVA;
	this->sim = &sim;
}

Metl::Metl(const Metl& rhs)
{
	Element::element_copy(rhs);
}


Metl::~Metl()
{
}
