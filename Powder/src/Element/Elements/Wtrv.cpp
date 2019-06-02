#include "Wtrv.h"
#include "Utils\Random.h"
#include "Simulation.h"

Element* Wtrv::clone_impl() const
{
	return new Wtrv(*this);
}

Wtrv::Wtrv(Simulation& sim)
{
	identifier = EL_WTRV;
	name = "Wtrv";
	description = "Wtrv";
	colors = { sf::Color(160, 160, 255) };
	color = colors[0];
	mass = 1.f;
	gas_gravity = -1.7f;
	gas_pressure = 0.0003f;
	restitution = 0.5f;
	temperature = 374.15f;
	thermal_cond = 0.0267f;
	specific_heat_cap = 1.864f;
	state = ST_GAS;
	low_temperature = 371.f;
	low_temperature_transition = EL_WATER;
	this->sim = &sim;
}

Wtrv::Wtrv(const Wtrv& rhs)
{
	Element::element_copy(rhs);
}


Wtrv::~Wtrv()
{
}
