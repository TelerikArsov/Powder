#include "PosP.h"
#include "Simulation.h"

void PosPTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	if (sim->bounds_check(x, y))
		sim->air.add_pressure(x, y, strength * 0.1f);
}

PosPTool::PosPTool()
{
	name = "PosPTool";
	description = "Adds positive pressure";
	identifier = TL_POSP;
	color = sf::Color::Magenta;
}

PosPTool::~PosPTool()
{
}