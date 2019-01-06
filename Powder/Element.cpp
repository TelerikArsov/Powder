#include "Element.h"
#include "Simulation.h"
#include <math.h>
//TODO implement an element to test this function properly
bool Element::move(Vector dest)
{
	bool status = true;
	int xD = dest.x;
	int yD = dest.y;
	if (x == xD && y == yD)
		return status;
	int xStep, yStep;
	int xO = x, yO = y;
	int dx = xD - xO;
	int dy = yD - yO;
	int e, eprev;
	if (dy < 0)
	{
		yStep = -1;
		dy = -dy;
	}
	else
	{
		yStep = 1;
	}
	if (dx < 0)
	{
		xStep = -1;
		dx = -dx;
	}
	else
	{
		xStep = 1;
	}
	int ddx = 2 * dx; // double for more precision
	int ddy = 2 * dy;
	// we check if the slope is in the 1st 4th 5th and 8th octant
	if (ddx >= ddy)
	{
		eprev = dx;
		e = dx;
		for (int i = 0; i < dx; i++)
		{
			xO += xStep;
			e += ddy;
			if (e > ddx)
			{
				yO += yStep;
				e -= ddx;
				if (e + eprev < ddx)  // bottom square also
				{
					if (!sim->bounds_check(xO, yO - yStep))
					{
						status = false;
						break;
					}
					// if there is no collision we update the elements real coordinates
					else if (sim->get_from_grid(xO, yO - yStep)->identifier != EL_NONE) //todo function that evals the collision
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO, yO - yStep);
						set_pos(xO, yO - yStep);
					}
				}
				else if (e + eprev > ddx) // left corner
				{
					if (!sim->bounds_check(xO - xStep, yO))
					{
						status = false;
						break;
					}
					else if (sim->get_from_grid(xO - xStep, yO)->identifier != EL_NONE)
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO - xStep, yO);
						set_pos(xO - xStep, yO);
					}
				}
				else //the corner case
				{
					// TODO
				}
			}
			if (!sim->bounds_check(xO, yO))
			{
				status = false;
				break;
			}
			else if (sim->get_from_grid(xO, yO)->identifier != EL_NONE)
			{
				status = false;
				break;
			}
			else
			{
				sim->swap_elements(x, y, xO, yO);
				set_pos(xO, yO);
			}
			eprev = e;
		}
	}
	else // if its in the other 4 octants
	{
		eprev = dy;
		e = dy;
		for (int i = 0; i < dy; i++)
		{
			yO += yStep;
			e += ddx;
			if (e > ddy)
			{
				xO += xStep;
				e -= ddy;
				if (e + eprev < ddy)
				{
					if (!sim->bounds_check(xO - xStep, yO))
					{
						status = false;
						break;
					}
					else if (sim->get_from_grid(xO - xStep, yO)->identifier != EL_NONE)
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO - xStep, yO);
						set_pos(xO - xStep,	y);
					}
				}
				else if (e + eprev > ddy)
				{
					if (!sim->bounds_check(xO, yO - yStep))
					{
						status = false;
						break;
					}
					else if (sim->get_from_grid(xO, yO - yStep)->identifier != EL_NONE)
					{
						status = false;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO, yO - yStep);
						set_pos(xO, yO - yStep);
					}
				}
				else
				{
				}
			}
			if (!sim->bounds_check(xO, yO))
			{
				status = false;
				break;
			}
			else if (sim->get_from_grid(xO, yO)->identifier != EL_NONE)
			{
				status = false;
				break;
			}
			else
			{
				sim->swap_elements(x, y, xO, yO);
				set_pos(xO, yO);
			}
			eprev = e;
		}
	}
	return status;
}

void Element::calc_loads()
{
	forces.Zero();
	forces += sim->base_g;
	Vector air_drag;
	double speed = velocity.Magnitude();
	air_drag = -velocity;
	// our y in the grid increases downwards
	// as opposed to the upward increase in the normal cartesian grid
	// and the velocity y is the one we use not the normal cartesian
	air_drag.y = -air_drag.y;
	air_drag.Normalize();
	air_drag *= 0.5 * sim->air_density * speed * speed * 
		(1) * drag_coef;
	//forces += air_drag;
}

void Element::update_velocity(double dt)
{
	calc_loads();
	Vector a;
	a = forces / mass;
	// our y in the grid increases downwards
	// as opposed to the upward increase in the normal cartesian grid
	a.y = -a.y;
	velocity += (a * dt);
	if (abs(velocity.Magnitude()) > terminal_vel)
	{
		velocity = terminal_vel_v;
	}
}

void Element::calc_term_vel() 
{
	terminal_vel_v = 2 * sim->base_g * mass / sim->air_density * 1 * drag_coef;
	terminal_vel_v.x = sqrt(abs(terminal_vel_v.x));
	terminal_vel_v.y = sqrt(abs(terminal_vel_v.y));
	terminal_vel = terminal_vel_v.Magnitude();
}

void Element::set_pos(int x, int y)
{
	this->x = x;
	this->y = y;
	pos.x = x;
	pos.y = y;
}
