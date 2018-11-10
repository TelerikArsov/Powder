#include "Simulation.h"
#include <algorithm>

void Simulation::tick()
{
	if (pause)
		return;
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
		elements_grid[(*add_it)->corr_y][(*add_it)->corr_x] = *add_it;
		add_it = add_queue.erase(add_it);
	}
	std::list<Element*>::iterator rem_it = remove_queue.begin();
	while (rem_it != remove_queue.end())
	{
		elements_grid[(*rem_it)->corr_y][(*rem_it)->corr_x] = nullptr;
		rem_it = remove_queue.erase(rem_it);
	}
}

void Simulation::render(sf::RenderWindow* window)
{
	for (auto &el : active_elements) 
	{
		el->render(cell_height, cell_width, window);
	}
	/*if (draw_grid)
	{
		for ()
	}*/
}

std::vector<Element*> Simulation::get_neighbours(int corr_x, int corr_y, std::string type)
{
	std::vector<Element*> neighbours;
	for (int i = -1 + corr_y; i < 2 + corr_y; i++)
	{
		for (int j = -1 + corr_x; j < 2 + corr_x; j++)
		{
			if (bounds_check(j, i) && elements_grid[i][j] != nullptr)
			{
				if (type != "" && elements_grid[i][j]->identifier != type)
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


bool Simulation::bounds_check(int corr_x, int corr_y) 
{
	return (corr_x >= 0 && corr_x < CELLS_X_COUNT) && (corr_y >= 0 && corr_y < CELLS_Y_COUNT);
}

bool Simulation::spawn_mouse(float mouse_x, float mouse_y) 
{
	int mouse_cell_x = (int) mouse_x / cell_width;
	int mouse_cell_y = (int) mouse_y / cell_height;
	if (elements_grid[mouse_cell_y][mouse_cell_x] == nullptr) 
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

Simulation::Simulation(float cell_height, float cell_width) :
	elements_count(0),
	draw_grid(false)
{
	this->cell_height = cell_height;
	this->cell_width = cell_width;
}

Simulation::~Simulation()
{

}
