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

int GOL::update(float dt) 
{
	if (state == 0)
		return EL_NONE_ID;
	for(int i = y - 1; i < y + 2; i++)
	{
		for (int j = x - 1; j < x + 2; j++)
		{
			if (i - y || j - x) 
			{
				if (sim->get_from_gol(j, i) == 0)
				{
					int size = sim->get_gol_neigh_count(j, i);
					sim->set_gol_at(j, i, 2);
					if (rules[B][size])
					{
						sim->create_element(identifier, false, false, j, i);
					}
				}
			}
		}

	}
	if (!rules[S][sim->get_gol_neigh_count(x, y)])
	{
		return EL_NONE_ID;
	}
	return identifier;
}

void GOL::draw_ui()
{
	Element::draw_ui();
	if (editor->string_prop(&rule_string, "GOL Rule"))
		process_rules();
}


GOL::~GOL()
{
}
