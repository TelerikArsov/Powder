#include "BRAN.h"
#include "Simulation.h"

int BRAN::update() 
{
	if (state == 0)
		return 1;
	for(int i = corr_y - 1; i < corr_y + 2; i++)
	{
		for (int j = corr_x - 1; j < corr_x + 2; j++)
		{
			if (sim->bounds_check(j, i) && (i - corr_y || j - corr_x)) 
			{
				if (sim->elements_grid[i][j] == nullptr)
				{
					int size = sim->get_neighbours(j, i).size();
					if (size == b_rule)
					{
						Element* new_cell = new BRAN(*this);
						new_cell->corr_x = j;
						new_cell->corr_y = i;
						sim->add_queue.push_back(new_cell);
					}
				}
			}
		}

	}
	int neig_count = sim->get_neighbours(corr_x, corr_y, identifier).size();
	if (neig_count != s_rule && neig_count != s_rule - 1)
	{
		return 1;
	}
	return 0;
}

void BRAN::render(float cell_height, float cell_width, sf::RenderWindow* window)
{
	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(cell_width, cell_height));
	cell.setFillColor(states_colors[state]);
	cell.setPosition(corr_x * cell_width, corr_y * cell_height);
	window->draw(cell);
}

Element* BRAN::clone() const
{
	return new BRAN(*this);
}

BRAN::BRAN() :
	state(1)
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
	state = rhs.state;
}

BRAN::~BRAN()
{
}
