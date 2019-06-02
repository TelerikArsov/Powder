#include "EXC4.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* EXC4::clone_impl() const
{
	return new EXC4(*this);
}

EXC4::EXC4(Simulation& sim)
{
	identifier = EL_EXC4;
	name = "EXC4";
	description = "EXC4";
	colors = { sf::Color(207, 127, 223) };
	color = colors[0];
	mass = 5;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 0.7f;
	specific_heat_cap = 3.f;
	endurance = 999;
	state = ST_SOLID;
	prop = Explosive | Explosive_Pressure;
	flammability = 1000.f;
	this->sim = &sim;
}

EXC4::EXC4(const EXC4& rhs)
{
	Element::element_copy(rhs);
}


EXC4::~EXC4()
{
}
