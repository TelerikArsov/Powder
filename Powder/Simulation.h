#pragma once
#include "Element.h"
#include <vector>
#include <list>
#include "None_Element.h"
#include "Brush.h"


class Simulation 
{
public:
	// the dimensions of each cell
	float cell_height, cell_width;		
	int cells_x_count, cells_y_count;
	// Not yet used
	int elements_count; 
	// The identifier of the current selected element
	int selected_element;
	int selected_brush;
	int mouse_x = 0, mouse_y = 0;
	std::vector<Brush* > brushes;
	std::vector<std::vector<Element* >> elements_grid;
	// Used for GoL simulation
	// 1 is alive 0 is dead, anything else varies
	// of the specific GoL element
	std::vector<std::vector<int>> gol_grid;
	// All currently active elements inside the element grid
	std::list<Element*> active_elements;
	// All the available elements that can be spawned
	std::vector<Element*> available_elements;
	// Elements that need to be added to the active list
	std::list<Element*> add_queue; 
	bool draw_grid = false;
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
	// Gets all the alive neighbours of a cell
	// with position x and y
	// Uses the gol_grid
	int get_gol_neigh_count(int x, int y);
	// Checks if the possition at x and y
	// is inside the grid
	bool bounds_check(int x, int y);
	// Spawns elements at the mouse position
	// Uses the spawn_area to determine the area in which the elements should be spawned
	void spawn_mouse();
	// Toggles the pause
	void pause();
	void set_mouse_cor(int x, int y);
	// If d > 0 then the spawn area increases
	// If d < 0 the spawn area decrease
	// Based on the currently used spawn area type the creation method is called
	// Spanw area types include circle, square, triangle NOTE: currently only cirlce is implemented 
	void resize_brush(int d);
	// int window_width, int window_height = the dimensions of the window 
	// where the simulation will be rendered
	Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height);
	~Simulation();
private:
	int spawn_width = 1, spawn_height = 1, spawn_radius = 1;
	bool paused = true;
};