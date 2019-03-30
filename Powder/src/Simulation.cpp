#include "Simulation.h"
#include <algorithm>
#include "Element/Elements/GOL.h"
#include "Utils/Vector.h"

static inline int IDX(int x, int y, int w)
{
	return y * w + x;
}

bool Simulation::check_if_empty(Vector cordinates) const
{
	return check_if_empty(cordinates.x, cordinates.y);
}

bool Simulation::check_if_empty(float x, float y) const
{
	return check_if_empty(static_cast<int>(floor(x)), static_cast<int>(floor(y)));
}

bool Simulation::check_if_empty(int x, int y) const
{
	bool res = false;
	if (bounds_check(x, y))
		res = elements_grid[IDX(x, y, cells_x_count)] == EL_NONE;
	return res;
}

Element* Simulation::get_from_grid(Vector cordinates) const
{
	return get_from_grid(cordinates.x, cordinates.y);
}

Element* Simulation::get_from_grid(float x, float y) const
{ 
	return get_from_grid(static_cast<int>(floor(x)), static_cast<int>(floor(y)));
}

Element* Simulation::get_from_grid(int x, int y) const
{
	Element* res = nullptr;
	if (bounds_check(x, y))
		res = elements_grid[IDX(x, y, cells_x_count)];
	return res;
}

int Simulation::get_from_gol(Vector cordinates) const
{
	return get_from_gol(cordinates.x, cordinates.y);
}

int Simulation::get_from_gol(float x, float y) const
{
	return get_from_gol(static_cast<int>(floor(x)), static_cast<int>(floor(y)));
}

int Simulation::get_from_gol(int x, int y) const
{
	int res = -1;
	if (bounds_check(x, y))
		res = gol_grid[IDX(x, y, cells_x_count)];
	return res;
}

void Simulation::set_gol_at(int x, int y, int val)
{
	if (bounds_check(x, y))
		gol_grid[IDX(x, y, cells_x_count)] = val;
}

Element* Simulation::find_by_id(int id)
{
	Element* match = nullptr;
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

Tool * Simulation::find_tool_by_id(int id)
{
	Tool* match = nullptr;
	for (auto tl : tools)
	{
		if (tl->identifier == id)
		{
			match = tl;
			break;
		}
	}
	return match;
}

void Simulation::tick(bool bypass_pause, float dt)
{
	fps = 1 / dt;
	if (paused && !bypass_pause)
		return;
	for (int i = 0; i < cells_y_count; i++)
	{
		for (int j = 0; j < cells_x_count; j++)
		{
			gol_grid[IDX(j, i, cells_x_count)] = elements_grid[IDX(j, i, cells_x_count)] != EL_NONE ? 1 : 0;
		}
	}

	active_elements.erase(std::remove_if(active_elements.begin(), active_elements.end(), 
		[this, dt](Element* el) -> bool
		{
			bool destroyed = el == EL_NONE;
			if (!destroyed)
			{
				int id = el->update(dt);
				int x = el->x, y = el->y;
				if(id != el->identifier)
				{	
					destroy_element(el);
					if(id != EL_NONE_ID)
						create_element(id, false, false, x, y);
					destroyed = true;
				}
			}
			return destroyed;
		}), active_elements.end());

	for (auto add_el : add_queue)
	{
		active_elements.push_back(add_el);		
	}
	add_queue.clear();
	if (neut_grav)
	{
		//doesnt make much sense for now, but if we change the base gravity of the simulation
		//we gotta update only with the new grav value, prob should be a method in grav class
		gravity->update_grav(neut_grav);
	}
	air->update_air();
}

void Simulation::render(sf::RenderWindow* window)
{
	baseUI->draw(this);
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
	if (drav_grid)
	{
		if(drav_grid == 1)
			window->draw(draw_grid(gravity->grav_grid, gravity->cell_size, gravity->grid_height, gravity->grid_width));
		if(drav_grid == 2)
			window->draw(draw_grid(air->velocity, air->cell_size, air->grid_height, air->grid_width));

	}
	sf::Vertex quad[4];
	// Only the outline is rendered
	for (auto &off : brushes[selected_brush]->get_outline()) 
	{
		int x = (mouse_cell_x + off.first);
		int y = (mouse_cell_y + off.second);
		quad[0].position = sf::Vector2f(x * cell_width, y * cell_height);				// this whole section should be in
		quad[1].position = sf::Vector2f((x + 1) * cell_width, y * cell_height);			// some kind of method (draw_rect: color, x, y, cell_sizes)
		quad[2].position = sf::Vector2f((x + 1) * cell_width, (y + 1) * cell_height);	// same thing is used in the element draw
		quad[3].position = sf::Vector2f(x * cell_width, (y + 1) * cell_height);

		quad[0].color = sf::Color(192, 192, 192); // hard coded should be part of the brush class
		quad[1].color = sf::Color(192, 192, 192);
		quad[2].color = sf::Color(192, 192, 192);
		quad[3].color = sf::Color(192, 192, 192);
		for(int i = 0; i < 4; i++)
			cells_vertices.append(quad[i]);
	} 
	window->draw(cells_vertices);
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
			if (bounds_check(j, i) && (i != corr_y || j != corr_x) 
				&& gol_grid[IDX(j, i, cells_x_count)] == 1)
			{
				// ignoring self
				count++;
			}
		}
	}
	return count;
}


bool Simulation::bounds_check(int corr_x, int corr_y) const
{
	return (corr_x >= 0 && corr_x < cells_x_count) && (corr_y >= 0 && corr_y < cells_y_count);
}

bool Simulation::create_element(int id, bool fm, bool ata, int x, int y)
{
	int idx = IDX(x, y, cells_x_count);
	// If the element at the position is None_Element (id == 0)
	if (bounds_check(x, y) && !(fm && !check_if_empty(x, y)))
	{
		Element* new_element;
		Element* tmp;
		id = fm ? selected_element : id;
		tmp = find_by_id(id);
		if (tmp)
			new_element = tmp->clone();
		else
			return false;
		new_element->set_pos(x, y, true);
		new_element->sim = this;

		if (ata)
			active_elements.push_back(new_element);
		else
			add_queue.push_back(new_element);

		delete elements_grid[idx];
		elements_grid[idx] = new_element;
		elements_count++;
		gravity->update_mass(new_element->mass, x, y, -1, -1);
		return true;
	}
	return false;
}

void Simulation::destroy_element(Element * destroyed)
{
	destroy_element(destroyed->x, destroyed->y);
}

void Simulation::destroy_element(int x, int y)
{
	int idx = IDX(x, y, cells_x_count);
	delete elements_grid[idx];
	elements_grid[idx] = EL_NONE;
	elements_count--;
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

bool Simulation::add_tool(Tool * tba)
{
	tools.push_back(tba);
	return true;
}

void Simulation::select_brush(int brushId)
{
	selected_brush = brushId;
}

void Simulation::select_element(int elementId)
{
	selected_tool = TL_SPWN;
	selected_element = elementId;
}

void Simulation::select_tool(int toolId)
{
	selected_tool = toolId;
	selected_element = -1;
}

void Simulation::swap_elements(int x1, int y1, int x2, int y2)
{
	//Prob will add more stuff then just this but for now...
	int idx1 = IDX(x1, y1, cells_x_count), idx2 = IDX(x2, y2, cells_x_count);
	Element* tmp = elements_grid[idx2];
	elements_grid[idx2] = elements_grid[idx1];
	elements_grid[idx1] = tmp;
	elements_grid[idx2]->set_pos(x2, y2, true);
	elements_grid[idx1]->set_pos(x1, y1, true);
}


void Simulation::mouse_left_click()
{
	for (auto &off : brushes[selected_brush]->get_area())
	{
		Tool* tool = find_tool_by_id(selected_tool);
		if(tool)
			tool->do_action(mouse_cell_x + off.first, mouse_cell_y + off.second, selected_element, this, 1);
	}
}

void Simulation::toggle_pause()
{
	paused = !paused;
}

void Simulation::set_mouse_coordinates(int x, int y)
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

Simulation::Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height, float base_g) :
	elements_count(0),
	gol_grid(cells_y_count * cells_x_count, 0),
	elements_grid(cells_y_count * cells_x_count, nullptr)
{
	this->cells_x_count = cells_x_count;
	this->cells_y_count = cells_y_count;
	this->cell_width = window_width / static_cast<float>(cells_x_count);
	this->cell_height = window_height / static_cast<float>(cells_y_count);
	selected_element = -1;
	selected_tool = TL_SPWN;
	selected_brush = 0;
	air = new Air(this, 4, 295.15f, 4);
	gravity = new Gravity(this, 10000, 25, 8, base_g, 1E-3f);
	baseUI = new BaseUI();
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
	delete baseUI;
}

sf::VertexArray Simulation::draw_grid(std::vector<Vector> velocities, int cell_size, int height, int width)
{
	sf::VertexArray grid(sf::Lines, height * width * 2);
	int g_i = 0;
	for (int i = 0; i < height * width; i++)
	{
		int x = i % width * cell_size + cell_size / 2;
		int y = i / width * cell_size + cell_size / 2;
		
		Vector dir(velocities[i].x * cell_size,
			velocities[i].y * cell_size);
		dir.Normalize() *= 4;
		grid[g_i] = sf::Vector2f(x * cell_width, y * cell_height);
		grid[g_i + 1] = sf::Vector2f((dir.x + x) * cell_width, (dir.y + y) * cell_height);
		g_i += 2;
	}
	sf::Vertex line[2];
	for (int i = 0; i < height - 1; i++)
	{
		line[0] = sf::Vector2f(0, (i + 1) * cell_size * cell_height);
		line[1] = sf::Vector2f(1000, (i + 1) * cell_size * cell_height);
		for (int i = 0; i < 2; i++)
			grid.append(line[i]);
	}
	for (int i = 0; i < width - 1; i++)
	{
		line[0] = sf::Vector2f((i + 1) * cell_size * cell_width, 0);
		line[1] = sf::Vector2f((i + 1) * cell_size * cell_width, 1000);
		for (int i = 0; i < 2; i++)
			grid.append(line[i]);
	}
	return grid;
}
