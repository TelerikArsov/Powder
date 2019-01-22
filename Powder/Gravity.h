#pragma once
#include <vector>
#include <list>
#include "Vector.h"

struct grav_cell {
	double mass;
	Vector grav_force;
	grav_cell(double mass, Vector grav_force)
		: mass(mass),
		grav_force(grav_force)
	{}
};

class Gravity
{
public:
	int cell_size;
	int grid_width;
	int grid_height;
	double mass_threshold;
	int distance_threshold;
	std::vector<grav_cell> grav_grid;
	std::list<int> active_cells;
	void update_mass(double mass, int new_x, int new_y, int old_x, int old_y);
	void update_grav();
	Vector get_force(int x, int y, double mass);
	Gravity(double mass_th, int dis_th, int cell_size, int sim_cellx_count, int sim_celly_count);
	Gravity();
	~Gravity();
};

