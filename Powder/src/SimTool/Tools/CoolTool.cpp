#include "CoolTool.h"
#include "Simulation.h"

void CoolTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	sim->GetFromGrid(x, y)->add_heat(-strength * 1000);
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