#pragma once
#include "Element.h"
#include <vector>
#include <list>
#include <string>

#define CELLS_X_COUNT 10
#define CELLS_Y_COUNT 10

class Simulation 
{
public:
	float cell_height, cell_width;
	int elements_count;
	Element* selected_element;
	Element* elements_grid[CELLS_X_COUNT][CELLS_Y_COUNT];
	std::list<Element*> active_elements;
	std::list<Element*> add_queue;
	std::list<Element*> remove_queue;
	bool pause = true;
	bool draw_grid;
	void tick();
	void render(sf::RenderWindow* window);
	std::vector<Element*> get_neighbours(int corr_x, int corr_y, std::string type = "");
	bool bounds_check(int corr_x, int corr_y);
	bool spawn_mouse(float mouse_x, float mouse_y);
	Simulation(float cell_height, float cell_width);
	~Simulation();
};