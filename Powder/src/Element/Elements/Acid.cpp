#include "Acid.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Acid::clone() const
{
	return new Acid(*this);
}

Acid::Acid(Simulation& sim)
{
	identifier = EL_ACID;
	name = "Acid";
	description = "Acid";
	colors = { sf::Color(236, 84, 254) };
	color = colors[0];
	mass = 1;
	restitution = 0.0f;
	temperature = 293.15f;
	thermal_cond = 0.013f;
	specific_heat_cap = 0.795f;
	endurance = 980;
	state = ST_LIQUID;
	prop = Corrosive | Igniter;
	this->sim = &sim;
}

Acid::Acid(const Acid& rhs)
{
	Element::element_copy(rhs);
	color = colors[random.between(0, colors.size() - 1)];
}


Acid::~Acid()
{
}
