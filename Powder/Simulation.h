#pragma once
#include "Element.h"
#include <vector>
#include <list>
#include "None_Element.h"


class Simulation 
{
public:
	float cell_height, cell_width;
	int cells_x_count, cells_y_count;
	int elements_count;
	Element* selected_element;
	std::vector<std::vector<Element*>> elements_grid;
	std::vector<std::vector<int>> gol_grid;
	std::list<Element*> active_elements;
	std::vector<Element*> available_elements;
	std::list<Element*> add_queue;
	std::list<Element*> remove_queue;
	bool pause = true;
	bool draw_grid;
	void tick();
	void render(sf::RenderWindow* window);
	std::vector<Element*> get_neighbours(int corr_x, int corr_y, int type = -1);
	int get_gol_neigh_count(int corr_x, int corr_y);
	bool bounds_check(int corr_x, int corr_y);
	bool spawn_mouse(int mouse_x, int mouse_y);
	Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height);
	~Simulation();
};