#include "NegP.h"
#include "Simulation.h"

void NegPTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	if (sim->bounds_check(x, y))
		sim->air.add_pressure(x, y, -strength * 0.1f);
}

NegPTool::NegPTool()
{
	name = "NegPTool";
	description = "Adds negative pressure";
	identifier = TL_NEGP;
	color = sf::Color::Cyan;
}

NegPTool::~NegPTool()
{
}