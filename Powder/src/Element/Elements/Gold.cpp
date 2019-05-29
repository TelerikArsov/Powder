#include "Gold.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Gold::clone() const
{
	return new Gold(*this);
}

Gold::Gold(Simulation& sim)
{
	identifier = EL_GOLD;
	name = "Gold";
	description = "Gold";
	colors = { sf::Color(219, 172, 43) };
	color = colors[0];
	mass = 10;
	restitution = 0.f;
	temperature = 295.15f;
	thermal_cond = 314.f;
	specific_heat_cap = 0.13f;
	endurance = 1000;
	state = ST_SOLID;
	prop = Corrosive_Res | Meltable;
	this->sim = &sim;
}

Gold::Gold(const Gold& rhs)
{
	Element::element_copy(rhs);
}


Gold::~Gold()
{
}
