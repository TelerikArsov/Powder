#include "Sand.h"
#include "Simulation.h"

bool Sand::update(double dt) 
{
	update_velocity(dt);
	Element * collided_elem = move(pos + velocity * dt);
	if (collision)
	{
		apply_impulse(collided_elem, dt);
		powder_pile();
	}
	return false;
}

void Sand::render(double cell_height, double cell_width, sf::Vertex * quad)
{
	quad[0].position = sf::Vector2f(x * cell_width, y * cell_height);
	quad[1].position = sf::Vector2f((x + 1) * cell_width, y * cell_height);
	quad[2].position = sf::Vector2f((x + 1) * cell_width, (y + 1) * cell_height);
	quad[3].position = sf::Vector2f(x * cell_width, (y + 1) * cell_height);

	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color =	color;
}

Element* Sand::clone() const
{
	return new Sand(*this);
}

Sand::Sand(Simulation& sim)
{
	identifier = EL_SAND; // TODO make enum
	name = "Sand";
	description = "Sand";
	menu_section = 2;
	state = 1;
	color = sf::Color::Yellow;
	mass = 1;
	restitution = 0.3;
	this->sim = &sim;
	calc_term_vel();
}

Sand::Sand(const Sand& rhs)
{
	identifier = rhs.identifier;
	name = rhs.name;
	description = rhs.description;
	color = rhs.color;
	drag_coef = rhs.drag_coef;
	menu_id = rhs.menu_id;
	menu_section = rhs.menu_section;
	endurance = rhs.endurance;
	x = rhs.x;
	y = rhs.y;
	mass = rhs.mass;
	restitution = rhs.restitution;
	terminal_vel = rhs.terminal_vel;
	terminal_vel_v = rhs.terminal_vel_v;
	temperature = rhs.temperature;
	meltable = rhs.meltable;
	state = rhs.state;
}


Sand::~Sand()
{
}
