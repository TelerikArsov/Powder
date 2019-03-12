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
	int ddx = 2 * dx; // float for more precision
	int ddy = 2 * dy;
	// we check if the slope is in the 1st 4th 5th and 8th octant
	if (ddx >= ddy)
	{
		move_helper(x, y, dx, xStep, yStep, ddx, ddy, false, coll_el);
	}
	else // if its in the other 4 octants
	{
		move_helper(x, y, dy, xStep, yStep, ddy, ddx, true, coll_el);
	}
	sim->gravity->update_mass(mass, x, y, old_x, old_y);
	return coll_el;
}

void Element::move_helper(int xO, int yO, int d, int xStep, int yStep, int de, int dr, bool ytype, Element*& coll_el)
{
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
				do_move(diff_x, diff_y, coll_el);
				if (collision)
					break;
			}
			else if (e + eprev > de) // left corner
			{
				diff_x = xO - (!ytype ? xStep : 0);
				diff_y = yO - (ytype ? yStep : 0);
				do_move(diff_x, diff_y, coll_el);
				if (collision)
					break;
			}
			else //the corner case
			{
				// TODO
			}
		}
		do_move(xO, yO, coll_el);
		if (collision)
			break;
		eprev = e;
		moved = true;
	}
}

void Element::do_move(int diff_x, int diff_y, Element*& coll_el)
{
	if (!sim->bounds_check(diff_x, diff_y))
	{
		ground_coll.x = static_cast<float> (diff_x);
		ground_coll.y = static_cast<float> (diff_y);
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
			coll_el = this;
		}
	}
}


int Element::eval_col(Element* coll_el)
{
	if (coll_el == EL_NONE)
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
	air_drag *= 0.5f * sim->air_density * speed * speed *
	(0.5f) * drag_coef;
	forces += air_drag;
}

void Element::update_velocity(float dt)
{
	add_velocity(sim->air->get_force(x, y));
	calc_loads();
	Vector a;
	a = forces / mass;
	// our y in the grid increases downwards
	// as opposed to the upward increase in the normal cartesian grid
	a.ReverseY();
	add_velocity(a * dt);
}

void Element::set_pos(int x, int y, bool true_pos)
{
	if (this != EL_NONE)
	{
		this->x = x;
		this->y = y;
		if (true_pos)
		{
			pos.x = static_cast<float> (x);
			pos.y = static_cast<float> (y);
		}
	}
}

bool Element::powder_pile()
{
	bool status = false;
	if (speed > pile_threshold && collided_elem != this)
	{
		Vector perp = Vector(collided_elem->x - x, collided_elem->y - y).PerpendicularCW();
		if (!moved)
		{
			bool side = random.next_bool();
			perp = (side ? perp : -perp);
			
			status = (sim->check_if_empty(collided_elem->pos + perp) &&
				sim->check_if_empty(pos + perp));
			
			if (!status)
			{
				perp.Reverse();
				status = (sim->check_if_empty(collided_elem->pos + perp) &&
					sim->check_if_empty(pos + perp));
			}
			if(status)
				status = move(collided_elem->pos + perp);
		}
	}
	return status;
}

void Element::liquid_move()
{
	bool ground = (collided_elem == this);
	Vector perp = (ground ? ground_coll - pos :
		collided_elem->pos - pos).PerpendicularCW();

	bool side = random.next_bool();
	perp = (side ? perp : -perp);

	bool status = sim->check_if_empty(pos + perp);

	if (!status)
	{
		perp.Reverse();
		status = sim->check_if_empty(pos + perp);
	}
	if (status)
		move(pos + perp);
}


void Element::apply_impulse(Element* coll_el, float dt)
{
	bool ground = (coll_el == this);
	Vector vr = (ground ? velocity : velocity - coll_el->velocity);
	Vector d = (ground ? pos - ground_coll : pos - coll_el->pos);
	d.Normalize();
	float j = (-(1 + restitution) * (vr * d)) 
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

void Element::add_heat(float heat)
{
	temperature += (heat / (mass * 1000) / specific_heat_cap);
}

bool Element::update(float dt)
{
	bool to_be_destroyed = false;
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
		apply_impulse(collided_elem, dt);
		liquid_move();
	}
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i || j)
			{
				Element* el = sim->get_from_grid(x + j, y + i);
				if (el != EL_NONE && el->temperature < temperature)
				{
					float heat = thermal_cond * (temperature - el->temperature);
					el->add_heat(heat);
					add_heat(-heat);
				}
			}
		}
	}
	if (sim->air->get_pressure(x, y) <= low_pressure)
		to_be_destroyed = sim->create_element(low_pressure_transition, false, false, x, y);
	
	else if (sim->air->get_pressure(x, y) >= high_pressure)
		to_be_destroyed = sim->create_element(high_pressure_transition, false, false, x, y);
	
	else if (temperature <= low_temperature)
		to_be_destroyed = sim->create_element(low_temperature_transition, false, false, x, y);
	
	else if (temperature <= low_pressure)
		to_be_destroyed = sim->create_element(high_temperature_transition, false, false, x, y);

	return to_be_destroyed;
}

void Element::draw_ui()
{
	editor->float_prop(&drag_coef, "drag coeficent", 0.01f, 0.1f);
	editor->float_prop(&mass, "mass", 1.0f, 10.0f);
	editor->float_prop(&speed, "speed", 1.0f, 10.0f, DrawLineGraph);
	editor->int_prop(&endurance, "endurance", 1, 5);
	editor->int_prop(&pile_threshold, "piling threshold", 1, 3);
	editor->float_prop(&temperature, "temperature", 0.1f, 1.0f);
	editor->float_prop(&thermal_cond, "thermal conductivity", 0.01f, 1.0f);
	editor->float_prop(&specific_heat_cap, "specific heat capacity", 0.01f, 1.0f, SameLineAfter);
	editor->bool_prop(&meltable, "meltable");
}

Element::~Element()
{
	if (editor)
	{
		editor->detach();
	}
}

void Element::render(float cell_height, float cell_width, sf::Vertex* quad)
{
	for (int i = 0; i < 4; i++)
	{
		quad[i].position = sf::Vector2f((x + ((i == 1 || i == 2) ? 1 : 0)) * cell_width, 
			(y + ((i == 2 || i == 3) ? 1 : 0)) * cell_height);
		quad[i].color = color;
	}
}