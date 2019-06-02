#include "Wood.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Wood::clone_impl() const
{
	return new Wood(*this);
}

Wood::Wood(Simulation& sim)
{
	identifier = EL_WOOD;
	name = "Wood";
	description = "Wood";
	colors = { sf::Color(191, 159, 63) };
	color = colors[0];
	mass = 5;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 1.17f;
	specific_heat_cap = 2.f;
	endurance = 985;
	state = ST_SOLID;
	prop = Flammable | Life_Dependant;
	flammability = 15.f;
	spontaneous_combustion_tmp = 573.15f;
	life = 4000.f;
	this->sim = &sim;
}

Wood::Wood(const Wood& rhs)
{
	Element::element_copy(rhs);
}


Wood::~Wood()
{
}
