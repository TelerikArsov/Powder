#include "Simulation.h"
#include <algorithm>
#include "Elements\GOL.h"
#include "Elements\None_Element.h"
#include "Vector.h"

Element* Simulation::get_from_grid(double x, double y)
{
	return get_from_grid(static_cast<int>(floor(x)), static_cast<int>(floor(y)));
}

Element * Simulation::get_from_grid(int x, int y)
{
	Element* res = nullptr;
	if (bounds_check(x, y))
		res = elements_grid[y * cells_x_count + x];
	return res;
}

int Simulation::get_from_gol(double x, double y)
{
	return get_from_gol(static_cast<int>(floor(x)), static_cast<int>(floor(y)));
}

int Simulation::get_from_gol(int x, int y)
{
	int res = -1;
	if (bounds_check(x, y))
		res = gol_grid[y][x];
	return res;
}

void Simulation::set_gol_el(int x, int y, int val)
{
	if (bounds_check(x, y))
		gol_grid[y][x] = val;
}

Element * Simulation::find_by_id(int id)
{
	Element * match = nullptr;
	for (auto el : available_elements)
	{
		if (el->identifier == id) 
		{
			match = el;
			break;
		}
	}
	return match;
}

void Simulation::tick(bool bypass_pause, double dt)
{
	if (paused && !bypass_pause)
		return;
	for (int i = 0; i < cells_y_count; i++)
	{
		for (int j = 0; j < cells_x_count; j++)
		{
			int idx = i * cells_x_count + j;
			gol_grid[i][j] = elements_grid[idx]->identifier != EL_NONE ? elements_grid[idx]->state : 0;
		}
	}
	for(auto i = active_elements.begin(); i != active_elements.end();)
	{
		if ((*i)->update(dt)) 
		{
			int x = (*i)->x, y = (*i)->y;
			i = active_elements.erase(i);
			int idx = y * cells_x_count + x;
			delete elements_grid[idx];
			elements_grid[idx] = new None_Element();
		}
		else 
		{
			++i;
		}
	}
	for (auto add_it = add_queue.begin(); add_it != add_queue.end(); add_it = add_queue.erase(add_it))
	{
		active_elements.push_back(*add_it);
	}
	if (neut_grav)
	{
		//doesnt make much sense for now but if we change the base gravity of the simulation
		//we gotta update only with the new grav value, prob should be a method in grav class
		gravity->update_grav(neut_grav);
	}
	air->update_air();
}

void Simulation::render(sf::RenderWindow* window)
{
	sf::VertexArray cells_vertices(sf::Quads, active_elements.size() * 4);
	if (active_elements.size() > 0)
	{
		int quad_i = 0;
		for (auto &el : active_elements)
		{
			el->render(cell_height, cell_width, &cells_vertices[quad_i * 4]);
			quad_i++;
		}
		
	}
	if (drav_grav_grid)
	{
		sf::VertexArray gravity_grid(sf::Lines, air->grid_height * air->grid_width * 2);
		int g_i = 0;
		for (int i = 0; i < air->grid_height * air->grid_width; i++)
		{
			double x1 = i % air->grid_width * air->cell_size + air->cell_size / 2;
			double y1 = i / air->grid_width * air->cell_size + air->cell_size / 2;
			//Vector dir(gravity->grav_grid[i].grav_force.x * gravity->cell_size,
			//	gravity->grav_grid[i].grav_force.y * gravity->cell_size);
			Vector dir(air->velocity[i].x * air->cell_size,
				air->velocity[i].y * air->cell_size);
			dir.Normalize() *= 4;
			gravity_grid[g_i] = sf::Vector2f(x1 * cell_width, y1 * cell_height);
			gravity_grid[g_i + 1] = sf::Vector2f((dir.x + x1) * cell_width, (dir.y + y1) * cell_height);
			g_i += 2;
		}
		for (int i = 0; i < air->grid_height - 1; i++)
		{
			sf::Vertex line[2];
			line[0] = sf::Vector2f(0, (i + 1) * air->cell_size * cell_height);
			line[1] = sf::Vector2f(1000, (i + 1) * air->cell_size * cell_height);
			for (int i = 0; i < 2; i++)
				gravity_grid.append(line[i]);
		}
		for (int i = 0; i < air->grid_width - 1; i++)
		{
			sf::Vertex line[2];
			line[0] = sf::Vector2f((i + 1) * air->cell_size * cell_width, 0);
			line[1] = sf::Vector2f((i + 1) * air->cell_size * cell_width, 1000);
			for (int i = 0; i < 2; i++)
				gravity_grid.append(line[i]);
		}
		window->draw(gravity_grid);
	}
	// Only the outline is rendered
	for (auto &off : brushes[selected_brush]->get_outline()) 
	{
		sf::Vertex quad[4];
		int mouse_cell_x = static_cast<int>(mouse_x / cell_width);
		int mouse_cell_y = static_cast<int>(mouse_y / cell_height);
		int x = (mouse_cell_x + off.first);
		int y = (mouse_cell_y + off.second);
		quad[0].position = sf::Vector2f(x * cell_width, y * cell_height);
		quad[1].position = sf::Vector2f((x + 1) * cell_width, y * cell_height);
		quad[2].position = sf::Vector2f((x + 1) * cell_width, (y + 1) * cell_height);
		quad[3].position = sf::Vector2f(x * cell_width, (y + 1) * cell_height);

		quad[0].color = sf::Color(192, 192, 192);
		quad[1].color = sf::Color(192, 192, 192);
		quad[2].color = sf::Color(192, 192, 192);
		quad[3].color = sf::Color(192, 192, 192);
		for(int i = 0; i < 4; i++)
			cells_vertices.append(quad[i]);
	}
	window->draw(cells_vertices);
	/*if (draw_grid)
	{
		for ()
	}*/
}


int Simulation::get_gol_neigh_count(int corr_x, int corr_y) const
{
	int count = 0;
	// Moore neighborhood is used
	for (int i = -1 + corr_y; i < 2 + corr_y; i++)
	{
		for (int j = -1 + corr_x; j < 2 + corr_x; j++)
		{
			// Only 1 in the gol_grid is considered alive
			if (bounds_check(j, i) && gol_grid[i][j] == 1)
			{
				// ignoring self
				if (i != corr_y || j != corr_x)
				{
					count++;
				}
			}
		}
	}
	return count;
}


bool Simulation::bounds_check(int corr_x, int corr_y) const
{
	return (corr_x >= 0 && corr_x < cells_x_count) && (corr_y >= 0 && corr_y < cells_y_count);
}

int Simulation::create_element(int id, bool fm, bool ata, int x, int y, std::string vars)
{
	int idx = y * cells_x_count + x;
	// If the element at the position is None_Element (id == 0)
	if (bounds_check(x, y) && elements_grid[idx]->identifier == EL_NONE)
	{
		Element* new_element;
		Element* tmp;
		// if creating from mouse
		// 1 from mouse 0 anything else
		if (fm == 1)
		{ 
			tmp = find_by_id(selected_element);
			if (tmp)
				new_element = tmp->clone();
			else
				return -1;
		}
		else
		{
			tmp = find_by_id(id);
			if (tmp)
				new_element = tmp->clone();
			else
				return -1;
			// GOL 
			if (id == EL_GOL)
			{
				if(vars != "")
				{ 
					dynamic_cast<GOL*>(new_element)->rule_string = vars;
					dynamic_cast<GOL*>(new_element)->process_rules();
				}
			}
		}
		new_element->set_pos(x, y, true);
		new_element->sim = this;
		if (ata)
		{
			active_elements.push_back(new_element);
		}
		else
		{
			add_queue.push_back(new_element);
		}
		delete elements_grid[idx];
		elements_grid[idx] = new_element;
		elements_count++;
		gravity->update_mass(new_element->mass, x, y, -1, -1);
		return 1;
	}
	return -1;
	
}

bool Simulation::add_element(Element * tba)
{
	for (auto el : available_elements) 
	{
		if (tba->identifier != EL_GOL && tba->identifier == el->identifier)
		{
			return false;
		}
	}
	available_elements.push_back(tba);
	return true;
}

bool Simulation::add_brush(Brush * tba)
{
	//for now its gonna be this, might add some more functionality later
	brushes.push_back(tba);
	return true;
}

void Simulation::swap_elements(int x1, int y1, int x2, int y2)
{
	//Prob will add more stuff then just this but for now...
	int idx1 = y1 * cells_x_count + x1, idx2 = y2 * cells_x_count + x2;
	Element* tmp = elements_grid[idx2];
	elements_grid[idx2] = elements_grid[idx1];
	elements_grid[idx1] = tmp;
	elements_grid[idx2]->set_pos(x2, y2, true);
	elements_grid[idx1]->set_pos(x1, y1, true);
}


void Simulation::spawn_at_mouse()
{
	for (auto &off : brushes[selected_brush]->get_area())
	{
		create_element(selected_element, true, true, mouse_cell_x + off.first, mouse_cell_y + off.second);
	}
}

void Simulation::pause()
{
	paused = !paused;
}

void Simulation::set_mouse_cor(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	mouse_cell_x = std::clamp(static_cast<int>(floor(mouse_x / cell_width)), 0, cells_x_count - 1);
	mouse_cell_y = std::clamp(static_cast<int>(floor(mouse_y / cell_height)), 0, cells_y_count - 1);
}

void Simulation::resize_brush(float d)
{
	brushes[selected_brush]->change_size(lrint(d));
}

Simulation::Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height, double base_g) :
	elements_count(0),
	draw_grid(false),
	gol_grid(cells_y_count, std::vector<int>(cells_x_count, 0))
{
	for (int i = 0; i < cells_y_count; i++)
	{
		for (int j = 0; j < cells_x_count; j++)
		{
			elements_grid.push_back(new None_Element());
		}
	}
	this->cells_x_count = cells_x_count;
	this->cells_y_count = cells_y_count;
	this->cell_width = window_width / static_cast<double>(cells_x_count);
	this->cell_height = window_height / static_cast<double>(cells_y_count);
	air = new Air(this, 0, 295.15, 4);
	gravity = new Gravity(this, 10000, 25, 8, base_g, 1E-3);
}

Simulation::~Simulation()
{
	for (auto& el : elements_grid)
	{
		delete el;
	}
	elements_grid.clear();
	for (auto& el : available_elements)
	{
		delete el;
	}
	available_elements.clear();
	delete gravity;
	delete air;
}
