#include "Sand.h"


bool Sand::update() 
{
	return false;
}

void Sand::render(float cell_height, float cell_width, sf::Vertex * quad)
{
	quad[0].position = sf::Vector2f(x * cell_width, y * cell_height);
	quad[1].position = sf::Vector2f((x + 1) * cell_width, y * cell_height);
	quad[2].position = sf::Vector2f((x + 1) * cell_width, (y + 1) * cell_height);
	quad[3].position = sf::Vector2f(x * cell_width, (y + 1) * cell_height);

	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color =	color;
}

Element * Sand::clone() const
{
	return new Sand(*this);
}

Sand::Sand()
{
	identifier = 1; // TODO make enum
	name = "Sand";
	description = "Sand";
	menu_section = 2;
	state = 1;
	color = sf::Color::Yellow;
}

Sand::Sand(const Sand& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	color = rhs.color;
	air_drag = rhs.air_drag;
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	endurance = rhs.endurance;
	x = rhs.x;
	y = rhs.y;
	weight = rhs.weight;
	temperature = rhs.temperature;
	meltable = rhs.meltable;
	state = rhs.state;
}


Sand::~Sand()
{
}
