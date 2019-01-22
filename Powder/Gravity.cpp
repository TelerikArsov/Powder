#include "Gravity.h"
#include <math.h>
#define G 6.674e-11

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
	if (old_mass < mass_threshold &&
		grav_grid[n_id].mass >= mass_threshold)
	{
		active_cells.push_back(n_id);
	}
	if (old_x != -1 && old_y != -1)
	{
		old_mass = grav_grid[o_id].mass;
		grav_grid[o_id].mass -= mass;
		if (old_mass >= mass_threshold &&
			grav_grid[o_id].mass < mass_threshold)
		{
			active_cells.remove(o_id);
		}
	}
}

void Gravity::update_grav()
{
	for (auto& el : grav_grid)
	{
		el.grav_force.Zero();
	}
	int oX, oY, nX, nY;
	for (int el : active_cells)
	{
		oX = el % grid_width;
		oY = el / grid_width;
		for (int i = -distance_threshold; i <= distance_threshold; i++)
		{
			for (int j = -distance_threshold; j <= distance_threshold; j++)
			{
				int distance_sq = i * i + j * j;
				if ((i != 0 || j != 0) && distance_sq <= distance_threshold * distance_threshold)
				{
					nX = oX + j;
					nY = oY + i;
					if (nX < 0 || nX >= grid_width || nY < 0 || nY >= grid_height)
						continue;
					int other_cell_index = nX + nY * grid_width;
					double gravity_force = (G * grav_grid[el].mass) / (distance_sq);
					grav_grid[other_cell_index].grav_force += Vector(oX - nX, oY - nY).Normalize() * gravity_force;
					//grav_grid[other_cell_index].grav_force.y = -grav_grid[other_cell_index].grav_force.y;
				}
			}
		}
	}
}

Vector Gravity::get_force(int x, int y, double mass)
{
	int cell_x = x / cell_size;
	int cell_y = y / cell_size;
	Vector force = grav_grid[cell_x + grid_width * cell_y].grav_force;
	force.y = -force.y;
	return force * mass;
}

Gravity::Gravity(double mass_th, int dis_th, int cell_size, int sim_cellx_count, int sim_celly_count)
{
	mass_threshold = mass_th;
	distance_threshold = dis_th;
	this->cell_size = cell_size;
	grid_width = std::ceil(static_cast<double>(sim_cellx_count) / cell_size);
	grid_height = std::ceil(static_cast<double>(sim_celly_count) / cell_size);
	for (int i = 0; i < grid_height; i++)
	{
		for (int j = 0; j < grid_width; j++)
		{
			grav_grid.emplace_back(0, Vector());
		}
	}
}

Gravity::Gravity()
{
}


Gravity::~Gravity()
{
}
