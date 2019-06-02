#include "Gun.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Gun::clone_impl() const
{
	return new Gun(*this);
}

Gun::Gun(Simulation& sim)
{
	identifier = EL_GUN;
	name = "Gunpowder";
	description = "Gunpowder";
	colors = { sf::Color(191, 191, 207) };
	color = colors[0];
	mass = 10;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 3.f;
	specific_heat_cap = 0.84f;
	endurance = 800;
	state = ST_POWDER;
	prop = Explosive;
	flammability = 900.f;
	this->sim = &sim;
}

Gun::Gun(const Gun& rhs)
{
	Element::element_copy(rhs);
}


Gun::~Gun()
{
}
