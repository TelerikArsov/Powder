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
	int cells_x_count, cells_y_count;
	int elements_count;
	int selected_element;
	std::vector<std::vector<Element* >> elements_grid;
	std::vector<std::vector<int>> gol_grid;
	std::list<Element*> active_elements;
	std::vector<Element*> available_elements;
	std::list<Element*> add_queue;
	bool draw_grid = false;
	void tick(bool bypass_pause = false);
	void render(sf::RenderWindow* window);
	int create_element(int id, bool from_mouse, bool add_to_active, int x, int y, std::string vars = "");
	void circle_create_area();
	int get_gol_neigh_count(int corr_x, int corr_y);
	bool bounds_check(int corr_x, int corr_y);
	void spawn_mouse();
	void pause();
	void set_mouse_cor(int x, int y);
	void resize_spawn(int d);
	Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height);
	~Simulation();
private:
	int spawn_width = 1, spawn_height = 1, spawn_radius = 1;//used to determine the area in which elements will be spawned 
	int mouse_x = 0, mouse_y = 0;
	std::vector<points> spawn_area;
	std::vector<points> spawn_outline;
	bool paused = true;
	void eight_fold_push(int x, int y, std::vector<points> &container);
	void four_fold_push(int x, int y, std::vector<points> &c);
	void sym_x_equal_y(int x, int y, std::vector<points> &c);
};