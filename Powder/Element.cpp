#include "Element.h"
#include "Simulation.h"
#include <math.h>
//TODO implement an element to test this function properly
Element* Element::move(Vector dest)
{
	Element* collided_elem = this;
	int xD = dest.x;
	int yD = dest.y;
	if (x == xD && y == yD)
		return collided_elem;
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
						ground_coll.x = xO;
						ground_coll.y = yO - yStep;
						collision = true;
						break;
					}
					collided_elem = sim->get_from_grid(xO, yO - yStep);
					// if there is no collision we update the elements real coordinates
					if (collided_elem->identifier != EL_NONE) //todo function that evals the collision
					{
						collision = true;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO, yO - yStep);
						set_pos(xO, yO - yStep);
						collided_elem = this;
					}
				}
				else if (e + eprev > ddx) // left corner
				{
					if (!sim->bounds_check(xO - xStep, yO))
					{
						ground_coll.x = xO - xStep;
						ground_coll.y = yO;
						collision = true;
						break;
					}
					collided_elem = sim->get_from_grid(xO - xStep, yO);
					if (collided_elem->identifier != EL_NONE)
					{
						collision = true;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO - xStep, yO);
						set_pos(xO - xStep, yO);
						collided_elem = this;
					}
				}
				else //the corner case
				{
					// TODO
				}
			}
			if (!sim->bounds_check(xO, yO))
			{
				ground_coll.x = xO;
				ground_coll.y = yO;
				collision = true;
				break;
			}
			collided_elem = sim->get_from_grid(xO, yO);
			if (collided_elem->identifier != EL_NONE)
			{
				collision = true;
				break;
			}
			else
			{
				sim->swap_elements(x, y, xO, yO);
				set_pos(xO, yO);
				collided_elem = this;
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
						ground_coll.x = xO - xStep;
						ground_coll.y = yO;
						collision = true;
						break;
					}
					collided_elem = sim->get_from_grid(xO - xStep, yO);
					if (collided_elem->identifier != EL_NONE)
					{
						collision = true;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO - xStep, yO);
						set_pos(xO - xStep,	y);
						collided_elem = this;
					}
				}
				else if (e + eprev > ddy)
				{
					if (!sim->bounds_check(xO, yO - yStep))
					{
						ground_coll.x = xO;
						ground_coll.y = yO - yStep;
						collision = true;
						break;
					}
					collided_elem = sim->get_from_grid(xO, yO - yStep);
					if (collided_elem->identifier != EL_NONE)
					{
						collision = true;
						break;
					}
					else
					{
						sim->swap_elements(x, y, xO, yO - yStep);
						set_pos(xO, yO - yStep);
						collided_elem = this;
					}
				}
				else
				{
				}
			}
			if (!sim->bounds_check(xO, yO))
			{
				ground_coll.x = xO;
				ground_coll.y = yO;
				collision = true;
				break;
			}
			collided_elem = sim->get_from_grid(xO, yO);
			if (collided_elem->identifier != EL_NONE)
			{
				collision = true;
				break;
			}
			else
			{
				sim->swap_elements(x, y, xO, yO);
				set_pos(xO, yO);
				collided_elem = this;
			}
			eprev = e;
		}
	}
	return collided_elem;
}

void Element::calc_loads()
{
	forces.Zero();
	
	if (collision)
	{
		forces += impact_forces;
		collision = false;
	}
	else
	{
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
			(0.5) * drag_coef;
		forces += air_drag;
	}
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
		velocity.Normalize();
		velocity *= terminal_vel;
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

void Element::powder_pile()
{
	//if(abs(velocity.Magnitude) >)
}

void Element::calc_impact_forces(Element* collided_elem, bool ground, double dt)
{
	impact_forces.Zero();
	Vector dv = ground ? velocity : velocity - collided_elem->velocity;
	Vector d = ground ? pos - ground_coll : pos - collided_elem->pos;
	d.Normalize();
	double test = -(dv * d) * (restitution + 1);
	double kg = 1 / mass + (ground ? 0 : 1 / collided_elem->mass);
	double J = -(dv * d) * (restitution + 1) / (1 / mass + (ground ? 0 : 1 / collided_elem->mass));
	Vector Fi = d;
	Fi *= J / dt;
	Fi.y = -Fi.y;
	impact_forces += Fi;
}
