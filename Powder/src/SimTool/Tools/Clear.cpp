#include "Clear.h"
#include "Simulation.h"

void ClearTool::do_action(int x, int y, int element_id, Simulation* sim, float strength)
{
	sim->destroy_element(x, y);
}

ClearTool::ClearTool()
{
	name = "Clear";
	description = "Default tool used for clearing";
	identifier = TL_CLEAR;
}


ClearTool::~ClearTool()
{
}
