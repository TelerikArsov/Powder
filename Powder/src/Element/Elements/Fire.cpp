#include "Fire.h"
#include "Utils\Random.h"

Element* Fire::clone() const
{
	return new Fire(*this);
}

Fire::Fire(Simulation& sim)
{
	identifier = EL_FIRE;
	name = "Fire";
	description = "Fire";
	colors = {sf::Color::Red};
	color = colors[0];
	mass = 0.01;
	gas_gravity = -1.f;
	gas_pressure = 0.001f;
	restitution = 0.f;
	temperature = 573.15f;
	thermal_cond = 2;
	specific_heat_cap = 0.8f;
	life_decay = true;
	life_dependant = true;
	state = ST_GAS;
	this->sim = &sim;
}

Fire::Fire(const Fire& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	colors = rhs.colors;
	color = colors[0];
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	set_pos(rhs.x, rhs.y, true);
	drag_coef = rhs.drag_coef;
	mass = rhs.mass;
	gas_gravity = rhs.gas_gravity;
	gas_pressure = rhs.gas_pressure;
	endurance = rhs.endurance;
	restitution = rhs.restitution;
	pile_threshold = rhs.pile_threshold;
	temperature = rhs.temperature;
	thermal_cond = rhs.thermal_cond;
	specific_heat_cap = rhs.specific_heat_cap;
	life = random.between(100, 220);
	meltable = rhs.meltable;
	life_decay = rhs.life_decay;
	life_dependant = rhs.life_dependant;
	tmp_velocity = rhs.tmp_velocity;
	state = rhs.state;
}


Fire::~Fire()
{
}
