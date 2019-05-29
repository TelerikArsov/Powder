#include "Dust.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Dust::clone() const
{
	return new Dust(*this);
}

Dust::Dust(Simulation& sim)
{
	identifier = EL_DUST;
	name = "SawDust";
	description = "Sawdust wood w";
	colors = { sf::Color(254, 223, 159) };
	color = colors[0];
	mass = 1;
	restitution = 0.f;
	pile_threshold = 0;
	temperature = 295.15f;
	thermal_cond = 1.08f;
	specific_heat_cap = 0.9f;
	endurance = 30;
	state = ST_POWDER;
	prop = Flammable | Life_Dependant;
	flammability = 40;
	life = 2000.f;
	spontaneous_combustion_tmp = 573.15f;
	this->sim = &sim;
}

Dust::Dust(const Dust& rhs)
{
	Element::element_copy(rhs);
}


Dust::~Dust()
{
}
