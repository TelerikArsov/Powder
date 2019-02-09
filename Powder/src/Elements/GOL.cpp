#include "GOL.h"
#include "Simulation.h"

void GOL::process_rules()
{
	for (auto& r : rules)
	{
		for (bool& vl : r)
		{
			vl = false;
		}
	}
	if (rule_string != "")
	{
		unsigned type = B;
		for (char c : rule_string) 
		{
			if (c == 'B' || c == 'b')
			{
				type = B;
			}
			else if (c == 'S' || c == 's')
			{
				type = S;
			}
			else if (c == '\\' || c == '/')
			{
				++type %= 3;
			}
			else if (c >= '0' || c < '9')
			{
				if (type == D)
				{
					if (c - '0' == 0)
					{
						continue;
					}
					rules[type][c - '0' - 1] = true;
				}
				else
				{
					rules[type][c - '0'] = true;
				}
			}
		}
	}
}

bool GOL::update(double dt) 
{
	if (state == 0)
		return true;
	for(int i = y - 1; i < y + 2; i++)
	{
		for (int j = x - 1; j < x + 2; j++)
		{
			if (i - y || j - x) 
			{
				if (sim->get_from_gol(j, i) == 0)
				{
					int size = sim->get_gol_neigh_count(j, i);
					sim->set_gol_el(j, i, 2);
					if (rules[B][size])
					{
						sim->create_element(identifier, false, false, j, i, rule_string);
					}
				}
			}
		}

	}
	if (!rules[S][sim->get_gol_neigh_count(x, y)])
	{
		return true;
	}
	return false;
}

void GOL::render(double cell_height, double cell_width, sf::Vertex* quad)
{
	quad[0].position = sf::Vector2f(x * cell_width, y * cell_height);
	quad[1].position = sf::Vector2f((x + 1) * cell_width, y * cell_height);
	quad[2].position = sf::Vector2f((x + 1) * cell_width, (y + 1) * cell_height);
	quad[3].position = sf::Vector2f(x * cell_width, (y + 1) * cell_height);

	quad[0].color = states_colors[state];
	quad[1].color = states_colors[state];
	quad[2].color = states_colors[state];
	quad[3].color = states_colors[state];
}

Element * GOL::clone() const
{
	return new GOL(*this);
}

GOL::GOL(int state, std::string name, std::string rules_s)
{
	identifier = 1;
	this->name = name;
	description = "Brians brain rules set for game of life";
	menu_section = 1;
	this->state = state;
	rule_string = rules_s;
	process_rules();
	mass = 100000;
}

GOL::GOL(const GOL& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	color = rhs.color;
	drag_coef = rhs.drag_coef;
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	endurance = rhs.endurance;
	x = rhs.x;
	y = rhs.y;
	mass = rhs.mass;
	temperature = rhs.temperature;
	meltable = rhs.meltable;
	state = rhs.state;
	rule_string = rhs.rule_string;
	process_rules();
}

GOL::~GOL()
{
}
