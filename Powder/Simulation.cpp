#include "Simulation.h"
#include <algorithm>
#include <GOL.h>

void Simulation::tick()
{
	if (pause)
		return;
	for (int i = 0; i < cells_y_count; i++)
	{
		for (int j = 0; j < cells_x_count; j++)
		{
			gol_grid[i][j] = elements_grid[i][j]->identifier != -1 ? elements_grid[i][j]->state : 0;
		}
	}
	for(auto i = active_elements.begin(); i != active_elements.end();)
	{
		if ((*i)->update()) 
		{
			int x = (*i)->corr_x, y = (*i)->corr_y;
			//remove_queue.push_back(*i);
			i = active_elements.erase(i);
			delete elements_grid[y][x];
			elements_grid[y][x] = new None_Element();
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
	/*std::list<Element*>::iterator rem_it = remove_queue.begin();
	while (rem_it != remove_queue.end())
	{
		elements_grid[(*rem_it)->corr_y][(*rem_it)->corr_x] = new None_Element();
		rem_it = remove_queue.erase(rem_it);
	}*/
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
	for (auto &off : spawn_outline) 
	{
		sf::Vertex quad[4];
		int mouse_cell_x = static_cast<float>(mouse_x) / cell_width;
		int mouse_cell_y = static_cast<float>(mouse_y) / cell_height;
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

void Simulation::circle_create_area()
{
	spawn_area.clear();
	spawn_outline.clear();
	int x = 0;
	int y = spawn_radius;
	int dx = 0;
	int dy = -2 * spawn_radius;
	int i = y;
	int err = 1 - spawn_radius;
	four_fold_push(x, y, spawn_outline);
	four_fold_push(x, y, spawn_area);
	for (i = y - 1; i > x; i--)
	{
		four_fold_push(x, i, spawn_area);
	}
	while (x < y)
	{
		x++;
		if (err >= 0)
		{
			y--;
			err += 2 * (x - y) + 1;
		}
		else {
			err += 2 * x + 1;
		}
		if (x < y)
		{
			eight_fold_push(x, y, spawn_outline);
			eight_fold_push(x, y, spawn_area);
		}
		else if (x == y)
		{
			sym_x_equal_y(x, y, spawn_outline);
			sym_x_equal_y(x, y, spawn_area);
		}
		for (i = y - 1; i > x; i--) {
			eight_fold_push(x, i, spawn_area);
		}
		if (i == x)
		{
			sym_x_equal_y(x, i, spawn_area);
		}
	}
	spawn_area.push_back(std::make_pair(0, 0));

}

void Simulation::eight_fold_push(int x, int y, std::vector<points> &c) 
{
	c.push_back(std::make_pair(x, y));
	c.push_back(std::make_pair(-x, y));
	c.push_back(std::make_pair(x, -y));
	c.push_back(std::make_pair(-x, -y));
	c.push_back(std::make_pair(y, x));
	c.push_back(std::make_pair(-y, x));
	c.push_back(std::make_pair(y, -x));
	c.push_back(std::make_pair(-y, -x));
}

void Simulation::four_fold_push(int x, int y, std::vector<points> &c)
{
	c.push_back(std::make_pair(x, y));
	c.push_back(std::make_pair(x, -y));
	c.push_back(std::make_pair(y, x));
	c.push_back(std::make_pair(-y, x));
}

void Simulation::sym_x_equal_y(int x, int y, std::vector<points> &c)
{
	c.push_back(std::make_pair(x, y));
	c.push_back(std::make_pair(x, -y));
	c.push_back(std::make_pair(-x, -y));
	c.push_back(std::make_pair(-x, y));
}


int Simulation::get_gol_neigh_count(int corr_x, int corr_y)
{
	int count = 0;
	for (int i = -1 + corr_y; i < 2 + corr_y; i++)
	{
		for (int j = -1 + corr_x; j < 2 + corr_x; j++)
		{
			if (bounds_check(j, i) && gol_grid[i][j] == 1)
			{
				if (i != corr_y || j != corr_x)
				{
					count++;
				}
			}
		}
	}
	return count;
}


bool Simulation::bounds_check(int corr_x, int corr_y) 
{
	return (corr_x >= 0 && corr_x < cells_x_count) && (corr_y >= 0 && corr_y < cells_y_count);
}

int Simulation::create_element(int id, bool fm, bool ata, int x, int y, std::string vars)
{
	if (bounds_check(x, y) && elements_grid[y][x]->identifier == -1)
	{
		Element* new_element;
		//if creating from mouse
		// 1 from mouse 0 anything else
		if (fm == 1)
		{
			new_element = available_elements[selected_element]->clone();
		}
		else
		{
			new_element = available_elements[id]->clone();
			// TO DO: enum with all the elements in it
			// to be more readable
			// GOL 
			if (id == 0)
			{
				if(vars != "")
				{ 
					dynamic_cast<GOL*>(new_element)->rule_string = vars;
					dynamic_cast<GOL*>(new_element)->process_rules();
				}
			}
		}
		new_element->corr_x = x;
		new_element->corr_y = y;
		new_element->sim = this;
		if (ata)
		{
			active_elements.push_back(new_element);
		}
		else
		{
			add_queue.push_back(new_element);
		}
		delete elements_grid[y][x];
		elements_grid[y][x] = new_element;
		elements_count++;

	}
	return -1;
	
}

bool Simulation::spawn_mouse()
{
	int mouse_cell_x = static_cast<float>(mouse_x) / cell_width;
	int mouse_cell_y = static_cast<float>(mouse_y) / cell_height;
	for (auto &off : spawn_area)
	{
		create_element(selected_element, true, true, mouse_cell_x + off.first, mouse_cell_y + off.second);
	}
	return true;
}

Simulation::Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height) :
	elements_count(0),
	draw_grid(false),
	gol_grid(cells_y_count, std::vector<int>(cells_x_count, 0))
{
	for (int i = 0; i < cells_y_count; i++)
	{
		elements_grid.push_back(std::vector<Element*>());
		for (int j = 0; j < cells_x_count; j++)
		{
			elements_grid[i].push_back(new None_Element());
		}
	}
	this->cells_x_count = cells_x_count;
	this->cells_y_count = cells_y_count;
	this->cell_width = static_cast<float>(window_width) / cells_x_count;
	this->cell_height = static_cast<float>(window_height) / cells_y_count;
	circle_create_area();
}

Simulation::~Simulation()
{

}
