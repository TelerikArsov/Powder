#include "Nitr.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Nitr::clone_impl() const
{
	return new Nitr(*this);
}

Nitr::Nitr(Simulation& sim)
{
	identifier = EL_NITR;
	name = "Nitroglycerin";
	description = "Nitroglycerin";
	colors = { sf::Color(31, 223, 15) };
	color = colors[0];
	mass = 1;
	restitution = 0.0f;
	temperature = 293.15f;
	thermal_cond = 1.56f;
	specific_heat_cap = 1.f;
	state = ST_LIQUID;
	prop = Explosive | Explosive_Pressure;
	flammability = 1000.f;
	this->sim = &sim;
}

Nitr::Nitr(const Nitr& rhs)
{
	Element::element_copy(rhs);
	color = colors[random.between(0, colors.size() - 1)];
}


Nitr::~Nitr()
{
}
