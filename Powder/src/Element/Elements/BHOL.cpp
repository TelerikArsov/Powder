#include "BHOL.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* BHOL::clone() const
{
	return new BHOL(*this);
}

BHOL::BHOL(Simulation& sim)
{
	identifier = EL_BHOL;
	name = "BHOL";
	description = "Mass always equal to the mass threshold of the gravity.Needs newtonian gravity to work";
	colors = { sf::Color(44, 44, 44) };
	color = colors[0];
	mass = sim.gravity->mass_th;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 1.f;
	specific_heat_cap = 1.f;
	endurance = 1000;
	state = ST_SOLID;
	this->sim = &sim;
}

BHOL::BHOL(const BHOL& rhs)
{
	Element::element_copy(rhs);
}


BHOL::~BHOL()
{
}
