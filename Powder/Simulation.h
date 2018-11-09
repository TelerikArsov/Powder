#pragma once
#include "Element.h"
#include <vector>

#define CELLS_X_COUNT 1024
#define CELLS_Y_COUNT 1024

class Simulation 
{
public:
	float cell_height, cell_width;
	int elements_count;
	Element* selected_element;
	Element* elements_grid[CELLS_X_COUNT][CELLS_Y_COUNT];
	std::vector<Element*> active_elements;
	bool draw_grid;
	void tick();
	void render();
	bool spawn(sf::Vector2i mouse_pos);
	Simulation(float cell_height, float cell_width);
	~Simulation();
private:
	bool pause;
};