#include "Coal.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Coal::clone() const
{
	return new Coal(*this);
}

Coal::Coal(Simulation& sim)
{
	identifier = EL_COAL;
	name = "Coal";
	description = "Coal";
	colors = { sf::Color(33, 33, 33) };
	color = colors[0];
	mass = 5;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 1.17f;
	specific_heat_cap = 2.f;
	endurance = 970;
	state = ST_SOLID;
	prop = Flammable | Life_dependant;
	flammability = 20.f;
	spotaneous_combustion_tmp = 422.04f;
	life = 6000.f;
	this->sim = &sim;
}

Coal::Coal(const Coal& rhs)
{
	Element::element_copy(rhs);
}


Coal::~Coal()
{
}
