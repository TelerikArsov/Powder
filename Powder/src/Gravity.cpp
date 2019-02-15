#include "Gravity.h"
#include "Simulation.h"
#include <math.h>

void Gravity::update_mass(double mass, int new_x, int new_y, int old_x, int old_y)
{
	int n_id = new_x / cell_size + grid_width * (new_y / cell_size);
	int o_id = old_x / cell_size + grid_width * (old_y / cell_size);
	if (n_id == o_id)
	{
		return;
	}
	double old_mass = grav_grid[n_id].mass;
	grav_grid[n_id].mass += mass;
	if (old_mass < mass_th &&
		grav_grid[n_id].mass >= mass_th)
	{
		active_cells.push_back(n_id);
	}
	if (old_x != -1 && old_y != -1)
	{
		old_mass = grav_grid[o_id].mass;
		grav_grid[o_id].mass -= mass;
		if (old_mass >= mass_th &&
			grav_grid[o_id].mass < mass_th)
		{
			active_cells.remove(o_id);
		}
	}
}

void Gravity::update_grav(bool neut_grav)
{
	for (auto& el : grav_grid)
	{
		el.grav_force = base_grav;
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
						// we multiply by cell_size because  distance is the distance between
						// the gravavity cells not the simulation cells
						grav_grid[other_cell_index].grav_force += Vector(oX - nX, oY - nY) * (G * grav_grid[el].mass) / 
							(distance_sq * sqrt(distance_sq) * cell_size * cell_size * cell_size);
						//grav_grid[other_cell_index].grav_force.y = -grav_grid[other_cell_index].grav_force.y;
					}
				}
			}
		}

	}
}

Vector Gravity::get_force(int x, int y, double mass)
{
	Vector force = grav_grid[x / cell_size + (y / cell_size * grid_width)].grav_force;
	force.y = -force.y;
	return force * mass;
}

Gravity::Gravity(Simulation* sim, double mass_threshold, int distance_threshold, int cell_size, double base_g, double g) : 
	mass_th(mass_threshold),
	dist_th(distance_threshold),
	cell_size(cell_size),
	G(g),
	sim(sim),
	grid_width(std::ceil(static_cast<double>(sim->cells_x_count) / cell_size)),
	grid_height(std::ceil(static_cast<double>(sim->cells_y_count) / cell_size))

{
	base_grav = Vector(0, 1) * base_g;
	for (int i = 0; i < grid_height; i++)
	{
		for (int j = 0; j < grid_width; j++)
		{
			grav_grid.emplace_back(0, base_grav);
		}
	}
}

Gravity::~Gravity()
{
}
