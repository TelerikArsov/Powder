#include "SpawnTool.h"
#include "Simulation.h"

void SpawnTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	sim->create_element(element_id, true, true, x, y);
}

SpawnTool::SpawnTool()
{
	name = "Spawn";
	description = "Default tool used for spawning";
	identifier = TL_SPWN;
}


SpawnTool::~SpawnTool()
{
}
