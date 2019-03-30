#include "CoolTool.h"
#include "Simulation.h"

void CoolTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	Element* el = sim->get_from_grid(x, y);
	if(el != EL_NONE)
		el->add_heat(-strength * 1000);
}

CoolTool::CoolTool()
{
	name = "Cool";
	description = "Adds negative heat to affected elements in an area";
	identifier = TL_COOL;
	color = sf::Color::Blue;
}

CoolTool::~CoolTool()
{
}