#include "WHOL.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* WHOL::clone_impl() const
{
	return new WHOL(*this);
}

int WHOL::update(float dt)
{
	if (mass < sim->gravity.mass_th)
	{
		sim->gravity.update_mass(mass, -1, -1, x, y);
		mass = -sim->gravity.mass_th;
		sim->gravity.update_mass(mass, x, y, -1, -1);
	}
	return identifier;
}

WHOL::WHOL(Simulation& sim)
{
	identifier = EL_WHOL;
	name = "WHOL";
	description = "Mass always equal to the negative of the mass threshold of the gravity. Needs newtonian gravity to work";
	colors = { sf::Color::White };
	color = colors[0];
	mass = -sim.gravity.mass_th;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 1.f;
	specific_heat_cap = 1.f;
	endurance = 1000;
	state = ST_SOLID;
	this->sim = &sim;
}

WHOL::WHOL(const WHOL& rhs)
{
	Element::element_copy(rhs);
}


WHOL::~WHOL()
{
}
