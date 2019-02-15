#include "Element.h"
#include "Simulation.h"
#include "Random.h"
#include <math.h>

Element* Element::move(Vector dest)
{
	collision = false;
	pos = dest;
	Element* coll_el = this;
	int xD = static_cast<int>(std::round(dest.x));
	int yD = static_cast<int>(std::round(dest.y));
	int old_x = x;
	int old_y = y;
	if (x == xD && y == yD)
		return coll_el;
	int xStep, yStep;
	int dx = xD - x;
	int dy = yD - y;
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
		coll_el = move_helper(x, y, dx, xStep, yStep, ddx, ddy, false);
	}
	else // if its in the other 4 octants
	{
		coll_el = move_helper(x, y, dy, xStep, yStep, ddy, ddx, true);
	}
	sim->gravity->update_mass(mass, x, y, old_x, old_y);
	return coll_el;
}

Element* Element::move_helper(int xO, int yO, int d, int xStep, int yStep, int de, int dr, bool ytype)
{
	Element* coll_el = this;
	int eprev = d, e = d;
	int diff_x, diff_y;
	for (int i = 0; i < d; i++)
	{
		ytype ? yO += yStep : xO += xStep;
		e += dr;
		if (e > de)
		{
			ytype ? xO += xStep : yO += yStep;
			e -= de;
			if (e + eprev < de)  // bottom square also
			{
				diff_x = xO - (ytype ? xStep : 0);
				diff_y = yO - (!ytype ? yStep : 0);
				coll_el = do_move(diff_x, diff_y);
				if (collision)
					break;
			}
			else if (e + eprev > de) // left corner
			{
				diff_x = xO - (!ytype ? xStep : 0);
				diff_y = yO - (ytype ? yStep : 0);
				coll_el = do_move(diff_x, diff_y);
				if (collision)
					break;
			}
			else //the corner case
			{
				// TODO
			}
		}
		coll_el = do_move(xO, yO);
		if (collision)
			break;
		eprev = e;
		moved = true;
	}
	return coll_el;
}

Element* Element::do_move(int diff_x, int diff_y)
{
	Element* coll_el = this;
	if (!sim->bounds_check(diff_x, diff_y))
	{
		ground_coll.x = diff_x;
		ground_coll.y = diff_y;
		set_pos(x, y, true);
		collision = true;
	}
	else
	{
		coll_el = sim->get_from_grid(diff_x, diff_y);
		// if there is no collision we update the elements real coordinates
		int res = eval_col(coll_el);
		if (res == C_BLOCK)
		{
			set_pos(x, y, true);
			collision = true;
		}
		else if(res == C_SWAP)
		{
			sim->swap_elements(x, y, diff_x, diff_y);
			set_pos(diff_x, diff_y, false);
			coll_el = this;
		}
	}
	
	return coll_el;
}


int Element::eval_col(Element* coll_el)
{
	if (coll_el->identifier == EL_NONE)
		return C_SWAP;
	if (coll_el->state == state)
		return mass > coll_el->mass ? C_SWAP : C_BLOCK;
	else
		return state > coll_el->state ? C_SWAP : C_BLOCK;
}



void Element::calc_loads()
{
	forces.Zero();
	collision = false;
	collided_elem = this;
	forces += sim->gravity->get_force(x, y, mass);
	Vector air_drag;
	air_drag = -velocity;
	// our y in the grid increases downwards
	// as opposed to the upward increase in the normal cartesian grid
	// and the velocity y is the one we use not the normal cartesian
	air_drag.ReverseY();
	air_drag.Normalize();
	air_drag *= 0.5 * sim->air_density * speed * speed *
	(0.5) * drag_coef;
	forces += air_drag;
}

void Element::update_velocity(double dt)
{
	calc_loads();
	Vector a;
	a = forces / mass;
	// our y in the grid increases downwards
	// as opposed to the upward increase in the normal cartesian grid
	a.ReverseY();
	add_velocity(a * dt);
	/*if (speed > terminal_vel)
	{
		velocity.Normalize();
		velocity *= terminal_vel;
	}*/
}

void Element::set_pos(int x, int y, bool true_pos)
{
	this->x = x;
	this->y = y;
	if(true_pos)
	{ 
		pos.x = x;
		pos.y = y;
	}
}

bool Element::powder_pile()
{
	bool status = false;
	if (speed > pile_threshold && collided_elem != this)
	{
		Vector dir_to_coll = Vector(collided_elem->x - x, collided_elem->y - y);
		Vector perp = dir_to_coll.PerpendicularCW();
		if (!moved)
		{
			bool side = random.next_bool();
			Vector check_pos = Vector(collided_elem->x, collided_elem->y);
			status = pile_helper(check_pos + (side ? perp : -perp));
			if (!status)
				status = pile_helper(check_pos + (side ? -perp : perp));
		}
	}
	return status;
}

bool Element::pile_helper(Vector check_pos)
{
	Element* res = sim->get_from_grid(check_pos.x, check_pos.y);
	if (res && res->identifier == EL_NONE)
	{
		move(check_pos);
		return !collision;
	}
	return false;
}

void Element::liquid_move()
{
	Vector dir_to_coll = Vector(collided_elem->x - x, collided_elem->y - y);
	Vector perp = dir_to_coll.PerpendicularCW();
	bool side = random.next_bool();
	move(pos + (side ? perp : -perp));
	if (collision)
		move(pos + (side ? -perp : perp));
}


void Element::apply_impulse(Element* coll_el, double dt)
{
	bool ground = (coll_el == this);
	Vector vr = (ground ? velocity : velocity - coll_el->velocity);
	Vector d = (ground ? pos - ground_coll : pos - coll_el->pos);
	d.Normalize();
	double j = (-(1 + restitution) * (vr * d)) 
		/ ((d * d) * (1 / mass + (ground ? 0 : 1 / coll_el->mass)));
	add_velocity(j * d / mass);
	if (!ground)
	{
		coll_el->add_velocity(-(j * d) / coll_el->mass);
	}
}

void Element::add_velocity(Vector nvelocity)
{
	velocity += nvelocity;
	speed = velocity.Magnitude();
}

void Element::add_heat(double heat)
{
	temperature += (heat / (mass * 1000) / specific_heat_cap);
}

bool Element::update(double dt)
{
	moved = false;
	update_velocity(dt);
	collided_elem = move(pos + (velocity * dt) / sim->scale);
	if (state == ST_POWDER && collision)
	{
		apply_impulse(collided_elem, dt);
		powder_pile();
	}
	if (state == ST_LIQUID && collision)
	{
		liquid_move();
	}
	add_velocity(sim->air->get_force(x, y));
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i || j)
			{
				Element* el = sim->get_from_grid(x + j, y + i);
				if (el && el->identifier != EL_NONE && el->temperature < temperature)
				{
					double heat = thermal_cond * (temperature - el->temperature);
					el->add_heat(heat);
					add_heat(-heat);
				}
			}
		}
	}
	return false;
}

void Element::render(double cell_height, double cell_width, sf::Vertex * quad)
{
	quad[0].position = sf::Vector2f(x * cell_width, y * cell_height);
	quad[1].position = sf::Vector2f((x + 1) * cell_width, y * cell_height);
	quad[2].position = sf::Vector2f((x + 1) * cell_width, (y + 1) * cell_height);
	quad[3].position = sf::Vector2f(x * cell_width, (y + 1) * cell_height);

	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color = color;
}