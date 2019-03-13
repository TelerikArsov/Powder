#pragma once
#include "SimTool\Tool.h"
#include "SimTool\ToolsIds.h"

class HeatTool :
	public Tool
{
public:
	void do_action(int x, int y, int element_id = -1, Simulation* sim = nullptr, float strength = 0.0f) override;
	HeatTool();
	~HeatTool();
};

