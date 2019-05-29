#include "Caus.h"
#include "Utils\Random.h"
#include "Simulation.h"

Element* Caus::clone() const
{
	return new Caus(*this);
}

Caus::Caus(Simulation& sim)
{
	identifier = EL_CAUS;
	name = "Caustic";
	description = "Caus";
	colors = { sf::Color(127, 254, 159) };
	color = colors[0];
	mass = 1.f;
	life = 23;
	gas_gravity = 0.f;
	gas_pressure = 0.001f;
	restitution = 1.f;
	temperature = 293.15f;
	thermal_cond = 0.05f;
	specific_heat_cap = 1.54f;
	state = ST_GAS;
	prop = Corrosive | Igniter | Life_Dependant;
	this->sim = &sim;
}

Caus::Caus(const Caus& rhs)
{
	Element::element_copy(rhs);
	life = static_cast<float>(random.between(100, 140));
}


Caus::~Caus()
{
}
