#include "Lava.h"
#include "Simulation.h"
#include "Utils/Random.h"

int Lava::update(float dt)
{
	int id = Element::update(dt);
	if (previous_id != EL_NONE_ID)
		id = previous_id;
	return id;
}

Element* Lava::clone_impl() const
{
	return new Lava(*this);
}

Lava::Lava(Simulation& sim)
{
	identifier = EL_LAVA;
	name = "Lava";
	description = "Lava";
	colors = { sf::Color(223, 79, 15) };
	color = colors[0];
	mass = 1;
	restitution = 0.0f;
	temperature = 1300.f;
	thermal_cond = 4.f;
	specific_heat_cap = 1.f;
	endurance = 998;
	state = ST_LIQUID;
	prop = Igniter;
	low_temperature = 1070.15f;
	low_temperature_transition = EL_STONE;
	this->sim = &sim;
}

Lava::Lava(const Lava& rhs)
{
	Element::element_copy(rhs);
	color = colors[random.between(0, colors.size() - 1)];
}


Lava::~Lava()
{
}
