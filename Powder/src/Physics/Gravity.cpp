#include "Gravity.h"
#include "Simulation.h"
#include <math.h>

void Gravity::resize()
{
	cell_size = std::clamp(cell_size, 1, 32);
	grid_width = static_cast<int>
		(std::ceil(static_cast<float>(sim->cells_x_count) / cell_size));
	grid_height = static_cast<int>
		(std::ceil(static_cast<float>(sim->cells_y_count) / cell_size));
	mass_grid.assign(grid_height * grid_width, 0);
	grav_grid.assign(grid_height * grid_width, base_grav);
}

void Gravity::set_baseG()
{
	base_grav = Vector(0, 1);
	base_grav *= base_g;
	update_grav(false);
}

void Gravity::update_mass(float mass, int new_x, int new_y, int old_x, int old_y)
{
	int n_id = new_x / cell_size + grid_width * (new_y / cell_size);
	int o_id = old_x / cell_size + grid_width * (old_y / cell_size);
	if (n_id == o_id)
	{
		return;
	}
	float old_mass;
	if (new_x != -1 && new_y != -1)
	{
		old_mass = mass_grid[n_id];
		mass_grid[n_id] += mass;
		if (old_mass < mass_th &&
			mass_grid[n_id] >= mass_th)
		{
			active_cells.push_back(n_id);
			changed = true;
		}
	}
	if (old_x != -1 && old_y != -1)
	{
		old_mass = mass_grid[o_id];
		mass_grid[o_id] -= mass;
		if (old_mass >= mass_th &&
			mass_grid[o_id] < mass_th)
		{
			active_cells.remove(o_id);
			changed = true;
		}
	}
}

void Gravity::update_grav(bool neut_grav)
{
	if (changed)
	{
		for (auto& el : grav_grid)
		{
			el = base_grav;
		}
		if (neut_grav)
		{
			// o stands for orignal, n new
			int oX, oY, nX, nY;
			for (int el : active_cells)
			{
				oX = el % grid_width;
				oY = el / grid_width;
				for (int i = -dist_th; i <= dist_th; i++)
				{
					for (int j = -dist_th; j <= dist_th; j++)
					{
						int distance_sq = i * i + j * j;
						if ((i != 0 || j != 0) && distance_sq <= dist_th * dist_th)
						{
							nX = oX + j;
							nY = oY + i;
							if (nX < 0 || nX >= grid_width || nY < 0 || nY >= grid_height)
								continue;
							int other_cell_index = nX + nY * grid_width;
							float distance_sqf = static_cast<float>(distance_sq);
							// we multiply by cell_size because  distance is the distance between
							// the gravavity cells not the simulation cells
							grav_grid[other_cell_index] += Vector(oX - nX, oY - nY) * (G * mass_grid[el]) /
								(distance_sqf * sqrtf(distance_sqf) * static_cast<float>(cell_size * cell_size * cell_size));
						}
					}
				}
			}

		}
		changed = false;
	}
}

Vector Gravity::get_force(int x, int y, float mass)
{
	Vector force = grav_grid[x / cell_size + (y / cell_size * grid_width)];
	force.y = -force.y;
	return force * mass;
}

Gravity::Gravity(Simulation* sim, float mass_threshold, int distance_threshold, int cell_size, float base_g, float g) : 
	mass_th(mass_threshold),
	dist_th(distance_threshold),
	cell_size(cell_size),
	G(g),
	base_g(base_g),
	sim(sim),
	grid_width(static_cast<int>(std::ceil(static_cast<float>(sim->cells_x_count) / cell_size))),
	grid_height(static_cast<int>(std::ceil(static_cast<float>(sim->cells_y_count) / cell_size))),
	mass_grid(grid_height * grid_width, 0)

{
	base_grav = Vector(0, 1) * base_g;
	for (int i = 0; i < grid_height; i++)
	{
		for (int j = 0; j < grid_width; j++)
		{
			grav_grid.push_back(base_grav);
		}
	}
}

Gravity::~Gravity()
{
}
