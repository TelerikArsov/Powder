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
	double G;
	double mass_th;
	int dist_th;
	int cell_size;
	int grid_width;
	int grid_height;
	Vector base_grav;
	std::vector<grav_cell> grav_grid;
	std::list<int> active_cells;
	void update_mass(double mass, int new_x, int new_y, int old_x, int old_y);
	void update_grav();
	Vector get_force(int x, int y, double mass);
	Gravity(double mass_threshold, int distance_threshold, int cell_size, int sim_cellx_count, int sim_celly_count, double base_grav, double g);
	~Gravity();
};

