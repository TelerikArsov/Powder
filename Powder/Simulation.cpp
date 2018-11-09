#include "Simulation.h"
#include <algorithm>
void Simulation::tick()
{
	active_elements.erase(
		std::remove_if(active_elements.begin(), 
			active_elements.end(),
			[](Element &el) -> bool { return !el.update(); }),
		active_elements.end());
}

void Simulation::render() 
{
	for (auto &el : active_elements) 
	{
		el->render(cell_height, cell_width);
	}
	/*if (draw_grid)
	{
		for ()
	}*/
}

bool Simulation::spawn(sf::Vector2i mouse_pos) 
{
	int mouse_cell_x = (int) mouse_pos.x / CELLS_X_COUNT;
	int mouse_cell_y = (int) mouse_pos.y / CELLS_Y_COUNT;
	if (elements_grid[mouse_cell_x][mouse_cell_y] != nullptr) 
	{
		Element* new_element = selected_element->clone();
		new_element->corr_x = mouse_cell_x;
		new_element->corr_y = mouse_cell_y;
		active_elements.push_back(new_element);
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
