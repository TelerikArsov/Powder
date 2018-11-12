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
	if (elements_grid[y][x]->identifier == -1)
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

bool Simulation::spawn_mouse(int mouse_x, int mouse_y)
{
	int mouse_cell_x = static_cast<float>(mouse_x) / cell_width;
	int mouse_cell_y = static_cast<float>(mouse_y) / cell_height;
	return create_element(selected_element, true, true, mouse_cell_x, mouse_cell_y);
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
}

Simulation::~Simulation()
{

}
