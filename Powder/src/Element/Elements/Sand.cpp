#include "Sand.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Sand::clone_impl() const
{
	return new Sand(*this);
}

Sand::Sand(Simulation& sim)
{
	identifier = EL_SAND;
	name = "Sand";
	description = "Sand";
	colors = {sf::Color(237, 201, 175), sf::Color(240, 222, 180)};
	color = colors[0];
	mass = 1;
	restitution = 0.f;
	pile_threshold = 0;
	temperature = 295.15f;
	thermal_cond = 2;
	specific_heat_cap = 0.8f;
	state = ST_POWDER;
	this->sim = &sim;
}

Sand::Sand(const Sand& rhs)
{
	Element::element_copy(rhs);
	color = colors[random.between(0, colors.size() - 1)];
}


Sand::~Sand()
{
}
