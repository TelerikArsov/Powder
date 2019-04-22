#include "Fire.h"
#include "Utils\Random.h"
#include "Simulation.h"

Element* Fire::clone() const
{
	return new Fire(*this);
}

Fire::Fire(Simulation& sim)
{
	identifier = EL_FIRE;
	name = "Fire";
	description = "Fire";
	colors = {sf::Color(255, 55, 0)};
	color = colors[0];
	mass = 1.f;
	gas_gravity = -1.f;
	gas_pressure = 0.001f;
	restitution = 0.f;
	temperature = 573.15f;
	thermal_cond = 2;
	specific_heat_cap = 0.8f;
	prop = Life_decay | Life_dependant | Igniter;
	state = ST_GAS;
	this->sim = &sim;
}

Fire::Fire(const Fire& rhs)
{
	Element::element_copy(rhs);
	life = static_cast<float>(random.between(100, 140));
}


Fire::~Fire()
{
}
