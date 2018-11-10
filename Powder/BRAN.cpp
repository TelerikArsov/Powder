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
				if (sim->gol_grid[i][j] == 0)
				{
					int size = sim->get_gol_neigh_count(j, i);
					sim->gol_grid[i][j] = 2;
					if (size == b_rule)
					{
						Element* new_cell = new BRAN(*this);
						new_cell->corr_x = j;
						new_cell->corr_y = i;
						new_cell->sim = sim;
						sim->add_queue.push_back(new_cell);
					}
				}
			}
		}

	}
	int neig_count = sim->get_gol_neigh_count(corr_x, corr_y);
	if (neig_count != 1 && neig_count != 2 && neig_count != 3 && neig_count != 4 && neig_count != 5)
	{
		return 1;
	}
	return 0;
}

void BRAN::render(float cell_height, float cell_width, sf::Vertex* quad)
{
	quad[0].position = sf::Vector2f(corr_x * cell_width, corr_y * cell_height);
	quad[1].position = sf::Vector2f((corr_x + 1) * cell_width, corr_y * cell_height);
	quad[2].position = sf::Vector2f((corr_x + 1) * cell_width, (corr_y + 1) * cell_height);
	quad[3].position = sf::Vector2f(corr_x * cell_width, (corr_y + 1) * cell_height);

	quad[0].color = states_colors[state];
	quad[1].color = states_colors[state];
	quad[2].color = states_colors[state];
	quad[3].color = states_colors[state];
}

Element* BRAN::clone() const
{
	return new BRAN(*this);
}

BRAN::BRAN(int id)
{
	identifier = id;
	name = "BRAN";
	description = "Brians brain rules set for game of life";
	color;
	menu_section = 1;
	state = 1;
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
