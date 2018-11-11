#include "Simulation.h"
#include <algorithm>

void Simulation::tick()
{
	if (pause)
		return;
	for (int i = 0; i < cells_y_count; i++)
	{
		for (int j = 0; j < cells_x_count; j++)
		{
			gol_grid[i][j] = elements_grid[i][j]->identifier != 0 ? elements_grid[i][j]->state : 0;
		}
	}
	std::list<Element*>::iterator i = active_elements.begin();
	while(i != active_elements.end())
	{
		if ((*i)->update()) 
		{
			remove_queue.push_back(*i);
			i = active_elements.erase(i);
		}
		else 
		{
			++i;
		}
	}
	std::list<Element*>::iterator add_it = add_queue.begin();
	while (add_it != add_queue.end())
	{
		active_elements.push_back(*add_it);
		//elements_grid[(*add_it)->corr_y][(*add_it)->corr_x];
		elements_grid[(*add_it)->corr_y][(*add_it)->corr_x] = *add_it;
		add_it = add_queue.erase(add_it);
	}
	std::list<Element*>::iterator rem_it = remove_queue.begin();
	while (rem_it != remove_queue.end())
	{
		//elements_grid[(*rem_it)->corr_y][(*rem_it)->corr_x];
		elements_grid[(*rem_it)->corr_y][(*rem_it)->corr_x] = new None_Element();
		rem_it = remove_queue.erase(rem_it);
	}
}

void Simulation::render(sf::RenderWindow* window)
{
	if (active_elements.size() > 0)
	{
		sf::VertexArray vertices;
		vertices.setPrimitiveType(sf::Quads);
		int quad_i = 0;
		vertices.resize(active_elements.size() * 4);
		for (auto &el : active_elements)
		{
			el->render(cell_height, cell_width, &vertices[quad_i * 4]);
			quad_i++;
		}
		window->draw(vertices);
	}
	/*if (draw_grid)
	{
		for ()
	}*/
}

std::vector<Element*> Simulation::get_neighbours(int corr_x, int corr_y, int type)
{
	std::vector<Element*> neighbours;
	for (int i = -1 + corr_y; i < 2 + corr_y; i++)
	{
		for (int j = -1 + corr_x; j < 2 + corr_x; j++)
		{
			if (bounds_check(j, i) && elements_grid[i][j]->identifier != 0)
			{
				if (type != -1 && elements_grid[i][j]->identifier != type)
				{
					continue;
				}
				if (i != corr_y || j != corr_x)
				{
					neighbours.push_back(elements_grid[i][j]);
				}
			}
		}
	}
	return neighbours;
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

bool Simulation::spawn_mouse(int mouse_x, int mouse_y) 
{
	int mouse_cell_x = static_cast<float>(mouse_x) / cell_width;
	int mouse_cell_y = static_cast<float>(mouse_y) / cell_height;
	if (elements_grid[mouse_cell_y][mouse_cell_x]->identifier == 0) 
	{
		Element* new_element = selected_element->clone();
		new_element->corr_x = mouse_cell_x;
		new_element->corr_y = mouse_cell_y;
		new_element->sim = this;
		active_elements.push_back(new_element);
		elements_grid[mouse_cell_y][mouse_cell_x] = new_element;
		elements_count++;
		return true;
	}
	return false;
}

Simulation::Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height) :
	elements_count(0),
	draw_grid(false),
	elements_grid(cells_y_count, std::vector<Element*>(cells_x_count, new None_Element())),
	gol_grid(cells_y_count, std::vector<int>(cells_x_count, 0))
{
	this->cells_x_count = cells_x_count;
	this->cells_y_count = cells_y_count;
	this->cell_width = static_cast<float>(window_width) / cells_x_count;
	this->cell_height = static_cast<float>(window_height) / cells_y_count;
}

Simulation::~Simulation()
{

}
