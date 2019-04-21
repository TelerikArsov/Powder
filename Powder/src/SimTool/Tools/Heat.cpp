#include "Heat.h"
#include "Simulation.h"

void HeatTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	Element* el = sim->get_from_grid(x, y);
	if(el)
		el->add_heat(strength * 1000);
}


HeatTool::HeatTool()
{
	name = "Heat";
	description = "Heats elements in the target area";
	identifier = TL_HEAT;
	color = sf::Color::Red;
}


HeatTool::~HeatTool()
{
}
