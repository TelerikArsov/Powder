#pragma once
#include "Element.h"
#include <vector>
#include <list>
#include "None_Element.h"


class Simulation 
{
	using points = std::pair<int, int>;
public:
	float cell_height, cell_width;
	int mouse_x = 0, mouse_y = 0;
	int spawn_width = 12, spawn_height;//used to determine the area in which elements will be spawned - for circle area we use this as radius
	std::vector<points> spawn_area;
	std::vector<points> spawn_outline;
	int cells_x_count, cells_y_count;
	int elements_count;
	int selected_element;
	std::vector<std::vector<Element* >> elements_grid;
	std::vector<std::vector<int>> gol_grid;
	std::list<Element*> active_elements;
	std::vector<Element*> available_elements;
	std::list<Element*> add_queue;
	std::list<Element*> remove_queue;
	bool pause = true;
	bool draw_grid = false;
	void tick();
	void render(sf::RenderWindow* window);
	int create_element(int id, bool from_mouse, bool add_to_active, int x, int y, std::string vars = "");
	void circle_spawn_area();
	int get_gol_neigh_count(int corr_x, int corr_y);
	bool bounds_check(int corr_x, int corr_y);
	bool spawn_mouse();
	Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height);
	~Simulation();
private:
	void eight_fold_push(int x, int y, std::vector<points> &container);
	void four_fold_push(int x, int y, std::vector<points> &c);
};