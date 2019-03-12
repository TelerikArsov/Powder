#pragma once
#include <vector>
#include <list>
#include "Utils/Vector.h"

class Simulation;

class Gravity
{
public:
	Simulation* sim;
	float G;
	float mass_th;
	float base_g;
	int dist_th;
	int cell_size;
	int grid_width;
	int grid_height;
	Vector base_grav;
	std::vector<Vector> grav_grid;
	std::vector<float> mass_grid;
	std::list<int> active_cells;
	void resize();
	void set_baseG();
	void update_mass(float mass, int new_x, int new_y, int old_x, int old_y);
	void update_grav(bool neut_grav);
	Vector get_force(int x, int y, float mass);
	Gravity(Simulation* sim, float mass_threshold, int distance_threshold, int cell_size, float base_g, float g);
	~Gravity();
};
