#pragma once
#include "Element.h"
#include "ElementsIds.h"
#include <vector>
#include <list>
#include "Brush.h"


class Simulation 
{
public:
	// The identifier of the current selected element
	int selected_element;
	int selected_brush;
	std::vector < std::vector<Element *>> get_element_grid() const;
	Element * get_from_grid(int x, int y) const;
	int get_from_gol(int x, int y) const;
	void set_gol_el(int x, int y, int val);
	Element * find_by_id(int id);
	// Updates the gol grid.
	// Loops over all the active elements and calls their update method.
	// If the update method returns true, then the elements is deleted.
	// Adds any newly created elements to the active list.
	void tick(bool bypass_pause = false);
	// Loops over all the active elements and calls their render method.
	// Renders the grid(NOT YET IMPLEMENTED) and the outline of the spawn area
	void render(sf::RenderWindow* window);
	// Creates element inside the grid
	//
	// bool from_mouse = whether the creation is called by the mouse
	// or from another existing element
	// int id = the identifier of the element to be created
	// bool add_to_active = whether the elements needs to be added to the active list
	// int x, y = the position of the element in the grid
	// string vars = any bonus information that might be needed in the creation of the element 
	int create_element(int id, bool from_mouse, bool add_to_active, int x, int y, std::string vars = "");
	void swap_elements(int x1, int y1, int x2, int y2);
	// creates the collision rules
	void init_col_rules();
	// used when the col rules is 3
	// returns 
	// 0 - block; the element is blocked from moving further
	// 1 - pass; both elements occupy the same space
	// 2 - swap; the elements switch places
	int eval_col(int x1, int y1, int x2, int y2);
	// Gets all the alive neighbours of a cell
	// with position x and y
	// Uses the gol_grid
	int get_gol_neigh_count(int x, int y) const;
	// Checks if the possition at x and y
	// is inside the grid
	bool bounds_check(int x, int y) const;
	// Spawns elements at the mouse position
	// Uses the spawn_area to determine the area in which the elements should be spawned
	void spawn_at_mouse();
	// Toggles the pause
	void pause();
	void set_mouse_cor(int x, int y);
	// If d > 0 then the spawn area increases
	// If d < 0 the spawn area decrease
	// Based on the currently used spawn area type the creation method is called
	// Spanw area types include circle, square, triangle NOTE: currently only cirlce is implemented 
	void resize_brush(int d);
	bool add_element(Element*);
	bool add_brush(Brush *);
	// int window_width, int window_height = the dimensions of the window 
	// where the simulation will be rendered
	Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height);
	~Simulation();
	//TODO something something encapsulation, most of the public properties should be here anyways
private:
	// the dimensions of each cell
	double cell_height, cell_width;
	int cells_x_count, cells_y_count;
	// Not yet used
	int elements_count;
	int mouse_x = 0, mouse_y = 0;
	std::vector<Brush* > brushes;
	std::vector<std::vector<Element* >> elements_grid;
	// Used for GoL simulation
	// 1 is alive 0 is dead, anything else varies
	// of the specific GoL element
	std::vector<std::vector<int>> gol_grid;
	// 0 - block; the element is blocked from moving further
	// 1 - pass; both elements occupy the same space
	// 2 - swap; the elements switch places
	// 3 - ambiguous; the eval function needs to detirmine the decision
	std::vector<std::vector<int>> collision_rules;
	// All the available elements that can be spawned
	std::vector<Element*> available_elements;
	// All currently active elements inside the element grid
	std::list<Element*> active_elements;
	// Elements that need to be added to the active list
	std::list<Element*> add_queue;
	bool draw_grid = false;
	int spawn_width = 1, spawn_height = 1, spawn_radius = 1;
	bool paused = true;
};