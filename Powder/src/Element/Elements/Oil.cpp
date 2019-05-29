#include "Oil.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* Oil::clone() const
{
	return new Oil(*this);
}

Oil::Oil(Simulation& sim)
{
	identifier = EL_OIL;
	name = "Oil";
	description = "Oil";
	colors = { sf::Color(63, 63, 15) };
	color = colors[0];
	mass = 1;
	restitution = 0.0f;
	temperature = 293.15f;
	thermal_cond = 0.15f;
	specific_heat_cap = 1.79f;
	state = ST_LIQUID;
	prop = Flammable | Life_Dependant;
	flammability = 20;
	life = 1000.f;
	high_temperature = 333.f;
	high_temperature_transition = EL_GAS;
	this->sim = &sim;
}

Oil::Oil(const Oil& rhs)
{
	Element::element_copy(rhs);
	color = colors[random.between(0, colors.size() - 1)];
}


Oil::~Oil()
{
}
