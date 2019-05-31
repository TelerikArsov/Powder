#include "Simulation.h"
#include <algorithm>
#include "Element/Elements/GOL.h"
#include "Utils/Vector.h"

bool Simulation::check_if_empty(Vector cordinates) const
{
	return check_if_empty(cordinates.x, cordinates.y);
}

bool Simulation::check_if_empty(float x, float y) const
{
	return check_if_empty(static_cast<int>(x), static_cast<int>(y));
}

bool Simulation::check_if_empty(int x, int y) const
{
	bool res = false;
	if (bounds_check(x, y))
		res = elements_grid[IDX(x, y, cells_x_count)] == EL_NONE;
	return res;
}

bool Simulation::check_id(Vector cordinates, int id) const
{
	return check_id(cordinates.x, cordinates.y, id);
}

bool Simulation::check_id(float x, float y, int id) const
{
	return check_id(static_cast<int>(x), static_cast<int>(y), id);
}

bool Simulation::check_id(int x, int y, int id) const
{
	bool res = false;
	if (bounds_check(x, y) && !check_if_empty(x, y))
		res = elements_grid[IDX(x, y, cells_x_count)]->identifier == id;
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
	match = static_cast<Element *>(find_simObject_byId(id, available_elements));
	return match;
}

Brush* Simulation::find_brush_by_id(int id)
{
	Brush* match = nullptr;
	match = static_cast<Brush *>(find_simObject_byId(id, brushes));
	return match;
}

Tool* Simulation::find_tool_by_id(int id)
{
	Tool* match = nullptr;
	match = static_cast<Tool *>(find_simObject_byId(id, tools));
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

	active_elements.remove_if([this, dt](Element* el) -> bool
		{
			bool destroyed = el == EL_NONE;
			if (!destroyed)
			{
				int id = el->update(dt);
				if(id != el->identifier)
				{	
					if (id != EL_NONE_ID)
						transition_element(el, id);
					else
						destroy_element(el, false);
					destroyed = true;
				}
			}
			return destroyed;
		});
	active_elements.splice(active_elements.end(), add_queue);
	if (neut_grav)
		gravity->update_grav();
	air->update_air();
	if (air->ambient_heat)
		air->update_airh();
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
			if (el != EL_NONE)
			{
				el->render(cell_height, cell_width, &cells_vertices[quad_i * 4]);
				quad_i++;
			}
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
	for (auto &off : selected_brush->get_outline()) 
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

Element* Simulation::create_element(int id, bool fm, bool ata, int idx)
{
	return create_element(id, fm, ata, idx % cells_x_count, idx / cells_x_count);
}

Element* Simulation::create_element(int id, bool fm, bool ata, int x, int y)
{
	// If the element at the position is None_Element (id == 0)
	if (bounds_check(x, y) && check_if_empty(x, y))
	{
		int idx = IDX(x, y, cells_x_count);
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

		elements_grid[idx] = new_element;
		elements_count++;
		gravity->update_mass(new_element->mass, x, y, -1, -1);
		return new_element;
	}
	return EL_NONE;
}
// for now it will only set the previous id and temperature
// of the new element
void Simulation::transition_element(Element* el, int id)
{
	int x = el->x, y = el->y;
	float temp = el->temperature;
	int old_id = el->identifier;
	destroy_element(x, y, false);
	Element* tmp = create_element(id, false, false, x, y);
	tmp->temperature = temp;
	tmp->previous_id = old_id;
}

void Simulation::destroy_element(Element* destroyed, bool dfa)
{
	destroy_element(destroyed->x, destroyed->y, dfa);
}

void Simulation::destroy_element(int x, int y, bool dfa)
{
	if (bounds_check(x, y) && !check_if_empty(x, y))
	{
		int idx = IDX(x, y, cells_x_count);
		if (dfa)
		{
			active_elements.remove_if(
				[x, y](Element* el) -> bool
				{ 
					return x == el->x && y == el->y;
				});
		}
		gravity->update_mass(elements_grid[idx]->mass, -1, -1, x, y);
		delete elements_grid[idx];
		elements_grid[idx] = EL_NONE;
		elements_count--;
	}
}

bool Simulation::add_element(Element* tba)
{
	// should think what to do about gol elements
	// prob. should inherit the main gol class and be other types of elements
	if (tba->identifier != EL_GOL)
	{
		return add_simObject(tba, available_elements);
	}
	return false;
}

bool Simulation::add_brush(Brush* tba)
{
	return add_simObject(tba, brushes);
}

bool Simulation::add_tool(Tool * tba)
{
	return add_simObject(tba, tools);
}

void Simulation::select_brush(int brushId)
{
	selected_brush = find_brush_by_id(brushId);
}

void Simulation::select_element(int elementId)
{
	selected_tool = find_tool_by_id(TL_SPWN);
	selected_element = elementId;
}

void Simulation::select_tool(int toolId)
{
	selected_tool = find_tool_by_id(toolId);
	selected_element = -1;
}

void Simulation::clear_field()
{
	for (int y = 0; y < cells_y_count; y++)
	{
		for (int x = 0; x < cells_x_count; x++)
		{
			destroy_element(x, y);
		}
	}
}

void Simulation::set_cell_count(int x_count, int y_count)
{
	if ((x_count != cells_x_count || y_count != cells_y_count) 
		&& x_count >= 10 && y_count >= 10)
	{
		clear_field();
		cells_x_count = x_count;
		cells_y_count = y_count;
		gol_grid.resize(x_count * y_count);
		elements_grid.assign(x_count * y_count, EL_NONE);
		if(air)
			air->resize();
		if(gravity)
			gravity->resize();
		cell_width = window_width / static_cast<float>(x_count);
		cell_height = window_height / static_cast<float>(y_count);
		mouse_calibrate();
	}
}

void Simulation::set_window_size(int window_w, int window_h)
{
	m_window_width = window_w;
	m_window_height = window_h;
	mouse_calibrate();
}

bool Simulation::add_simObject(SimObject* object, std::list<SimObject*>& container)
{
	for (auto ob : container)
	{
		if (object->identifier == ob->identifier)
		{
			return false;
		}
	}
	container.push_back(object);
	return true;
}

SimObject * Simulation::find_simObject_byId(int id, std::list<SimObject*>& list)
{
	SimObject* match = nullptr;
	for (auto ob : list)
	{
		if (ob->identifier == id)
		{
			match = ob;
			break;
		}
	}
	return match;
}

void Simulation::mouse_calibrate()
{
	if (cells_x_count && cells_y_count)
	{
		m_cell_width = m_window_width / static_cast<float>(cells_x_count);
		m_cell_height = m_window_height / static_cast<float>(cells_y_count);
	}
}
void Simulation::delete_simObjects(std::list<SimObject*> container)
{
	for (auto el : container)
	{
		delete el;
	}
}
void Simulation::swap_elements(int x1, int y1, int x2, int y2)
{
	//Prob will add more stuff then just this but for now...
	int idx1 = IDX(x1, y1, cells_x_count), idx2 = IDX(x2, y2, cells_x_count);
	Element* tmp = elements_grid[idx2];
	elements_grid[idx2] = elements_grid[idx1];
	elements_grid[idx1] = tmp;
	elements_grid[idx2]->set_pos(x2, y2, false);
	elements_grid[idx1]->set_pos(x1, y1, false);
}


void Simulation::mouse_left_click()
{
	for (auto &off : selected_brush->get_area())
	{
		if(selected_tool)
			selected_tool->do_action(mouse_cell_x + off.first, mouse_cell_y + off.second, selected_element, this, 1);
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
	mouse_cell_x = std::clamp(static_cast<int>(floor(mouse_x / m_cell_width)), 0, cells_x_count - 1);
	mouse_cell_y = std::clamp(static_cast<int>(floor(mouse_y / m_cell_height)), 0, cells_y_count - 1);
}

void Simulation::resize_brush(float d)
{
	selected_brush->change_size(lrint(d));
}

Simulation::Simulation(int x_count, int y_count, int window_w, int window_h, float base_g) :
	elements_count(0),
	gol_grid(y_count * x_count, 0),
	elements_grid(y_count * x_count, EL_NONE),
	cell_width(window_w / static_cast<float>(x_count)),
	cell_height(window_h / static_cast<float>(y_count)),
	cells_x_count(x_count),
	cells_y_count(y_count),
	window_height(window_h),
	window_width(window_w),
	m_window_height(window_h),
	m_window_width(window_w)
{ 
	mouse_calibrate();
	selected_element = EL_NONE_ID;
	selected_tool = nullptr;
	selected_brush = nullptr;
	air = new Air(this, 4, 295.15f, 4);
	gravity = new Gravity(this, 10000, 25, 8, base_g, 1E-3f);
	baseUI = new BaseUI();
}

Simulation::~Simulation()
{
	clear_field();
	delete_simObjects(available_elements);
	delete_simObjects(tools);
	delete_simObjects(brushes);
	delete gravity;
	delete air;
	delete baseUI;
}

sf::VertexArray Simulation::draw_grid(std::vector<Vector> velocities, int cell_size, int height, int width)
{
	sf::VertexArray grid(sf::Lines, height * width * 2);
	int g_i = 0;
	// velocities
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
	//the grid
	sf::Vertex line[2];
	for (int i = 0; i < height - 1; i++)
	{
		line[0] = sf::Vector2f(0, (i + 1) * cell_size * cell_height);
		line[1] = sf::Vector2f(static_cast<float>(window_width), (i + 1) * cell_size * cell_height);
		for (int i = 0; i < 2; i++)
			grid.append(line[i]);
	}
	for (int i = 0; i < width - 1; i++)
	{
		line[0] = sf::Vector2f((i + 1) * cell_size * cell_width, 0);
		line[1] = sf::Vector2f((i + 1) * cell_size * cell_width, static_cast<float>(window_height));
		for (int i = 0; i < 2; i++)
			grid.append(line[i]);
	}
	return grid;
}
