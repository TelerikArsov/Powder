#include "BRAN.h"


int BRAN::update() 
{
	if (state == 0)
		return 1;
	int a_neighbours;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++) 
		{

		}
	}
	return 0;
}

void BRAN::render(float cell_height, float cell_width)
{
	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(cell_width, cell_height));
	cell.setFillColor(states_colors[state]);
	cell.setPosition(corr_x * cell_width, corr_y * cell_height);
}

Element* BRAN::clone() const
{
	return new BRAN(*this);
}

BRAN::BRAN() :
	state(1),
	states_colors{ sf::Color::Blue, sf::Color::White }
{
	identifier = "GOL_BRAN";
	name = "BRAN";
	description = "Brians brain rules set for game of life";
	color;
	menu_section = 1;
}

BRAN::BRAN(const BRAN& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	color = rhs.color;
	air_drag = rhs.air_drag;
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	endurance = rhs.endurance;
	corr_x = rhs.corr_x;
	corr_y = rhs.corr_y;
	weight = rhs.weight;
	temperature = rhs.temperature;
	meltable = rhs.meltable;
}

BRAN::~BRAN()
{
}
