#include "Fire.h"
#include "Utils\Random.h"
#include "Simulation.h"

Element* Fire::clone() const
{
	return new Fire(*this);
}

int Fire::update(float dt)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((i || j) && !sim->check_if_empty(x + j, y + i) &&
				sim->bounds_check(x + j, y + i))
			{
				Element* target = sim->get_from_grid(x + j, y + i);
				if ((target->prop & Flammable) == Flammable &&
					(target->prop & Burning) != Burning &&
					random.chance(static_cast<int>(target->flammability), 1000))
					target->prop |= Burning;
			}
	return Element::update(dt);
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
	prop = Life_decay | Life_dependant;
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
