#include "Gas.h"
#include "Utils\Random.h"
#include "Simulation.h"

Element* Gas::clone() const
{
	return new Gas(*this);
}

Gas::Gas(Simulation& sim)
{
	identifier = EL_GAS;
	name = "Gas";
	description = "Gas";
	colors = { sf::Color(223, 254, 31) };
	color = colors[0];
	mass = 1.f;
	gas_gravity = 0.f;
	gas_pressure = 0.001f;
	restitution = 1.f;
	temperature = 297.15f;
	thermal_cond = 0.02f;
	specific_heat_cap = 2.34f;
	state = ST_GAS;
	prop = Flammable | Life_Dependant;
	flammability = 600.f;
	high_pressure = 6.f;
	high_pressure_transition = EL_OIL;
	this->sim = &sim;
}

Gas::Gas(const Gas& rhs)
{
	Element::element_copy(rhs);
}


Gas::~Gas()
{
}
