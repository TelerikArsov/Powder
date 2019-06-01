#include "WALL.h"
#include "Simulation.h"
#include "Utils/Random.h"

Element* WALL::clone() const
{
	return new WALL(*this);
}

WALL::WALL(Simulation& sim)
{
	identifier = EL_WALL;
	name = "WALL";
	description = "WALL GOL Rule";
	rule_string = "s2345/b45678";
	state = ST_SOLID;
	colors = { sf::Color(33, 77, 255) };
	color = colors[0];
	process_rules();
	this->sim = &sim;
}

WALL::WALL(const WALL& rhs)
{
	Element::element_copy(rhs);
	rule_string = rhs.rule_string;
	process_rules();
}

WALL::~WALL()
{
}
