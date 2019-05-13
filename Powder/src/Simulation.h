#pragma once
#include <vector>

#include "Element/Element.h"
#include "Element/ElementsIds.h"
#include "SimTool/Tool.h"
#include "SimTool/ToolsIds.h"
#include "UI/BaseUI.h" 
#include "Brushes/Brush.h"
#include "Physics/Gravity.h"
#include "Physics/Air.h"

class Vector;

class Simulation 
{
public:
	int elements_count;
	float fps = 0.0f;
	bool paused = true;
	int cells_x_count = 10, cells_y_count = 10;
	int mouse_cell_x, mouse_cell_y;
	// how fast heat heats up elements
	float heat_coef = 1.f; 
	// power of 10, not sure how to make it only a power of 10 
	float scale = 1.f;
	Gravity* gravity;
	Air* air;
	BaseUI* baseUI;
	bool neut_grav = false;
	// Set in the ui, used to know which grid to draw
	// either none = 0, grav = 1, air = 2
	int drav_grid = 0;
	bool check_if_empty(Vector cordinates) const;
	bool check_if_empty(float x, float y) const;
	bool check_if_empty(int x, int y) const;
	bool check_id(Vector cordinates, int id) const;
	bool check_id(float x, float y, int id) const;
	bool check_id(int x, int y, int id) const;
	Element* get_from_grid(Vector cordinates) const;
	Element* get_from_grid(float x, float y) const;
	Element* get_from_grid(int x, int y) const;
	int get_from_gol(Vector cordinates) const;
	int get_from_gol(float x, float y) const;
	int get_from_gol(int x, int y) const;
	// Gets all the alive neighbours of a cell
	// with position x and y
	// Uses the gol_grid
	int get_gol_neigh_count(int x, int y) const;
	void set_gol_at(int x, int y, int val);
	Element* find_by_id(int id);
	Tool* find_tool_by_id(int id);
	// Updates the gol grid.
	// Loops over all the active elements and calls their update method.
	// If the update method returns true, then the elements is deleted.
	// Adds any newly created elements to the active list.
	void tick(bool bypass_pause = false, float dt = 1);
	// Loops over all the active elements and calls their render method.
	// Renders the grid(NOT YET IMPLEMENTED) and the outline of the spawn area
	void render(sf::RenderWindow* window);
	bool create_element(int id, bool from_mouse, bool add_to_active, int idx);
	// Creates element inside the grid
	//
	// bool from_mouse = whether the creation is called by the mouse
	// or from another existing element
	// int id = the identifier of the element to be created
	// bool add_to_active = whether the elements needs to be added to the active list
	// int x, y = the position of the element in the grid
	bool create_element(int id, bool from_mouse, bool add_to_active, int x, int y);
	void destroy_element(Element* destroyed, bool destroy_from_active = true);
	void destroy_element(int x, int y, bool destroy_from_active = true);
	void swap_elements(int x1, int y1, int x2, int y2);
	// Checks if the possition at x and y
	// is inside the grid
	bool bounds_check(int x, int y) const;
	// Spawns elements at the mouse position
	// Uses the spawn_area to determine the area in which the elements should be spawned
	void mouse_left_click();
	// Toggles the pause
	void toggle_pause();
	void set_mouse_coordinates(int x, int y);
	// If d > 0 then the spawn area increases
	// If d < 0 the spawn area decrease
	// Based on the currently used spawn area type the creation method is called
	// Spanw area types include circle, square, triangle NOTE: currently only cirlce is implemented 
	void resize_brush(float d);
	bool add_element(Element*);
	bool add_brush(Brush *);
	bool add_tool(Tool *);
	void select_brush(int brushId);
	void select_element(int elementId);
	void select_tool(int toolId);
	void clear_field();
	void set_cell_count(int x_count, int y_count);
	void set_window_size(int window_width, int window_height);
	// int window_width, int window_height = the dimensions of the window 
	// where the simulation will be rendered
	Simulation(int cells_x_count, int cells_y_count, int window_width, int window_height, float base_g);
	~Simulation();
	//TODO something something encapsulation, most of the public properties should be here anyways
private:
	// the dimensions of each cell
	float cell_height, cell_width;
	float m_cell_height, m_cell_width;
	int const window_height, window_width;
	int m_window_height, m_window_width;
	// The identifier of the current selected element
	int selected_element;
	int selected_brush;
	int selected_tool;
	friend class BaseUI;
	int mouse_x = 0, mouse_y = 0;
	std::vector<Brush* > brushes;
	std::vector<Tool*> tools;
	std::vector<Element*> elements_grid;
	// Used for GoL simulation
	// 1 is alive 0 is dead, anything else varies
	// of the specific GoL element
	std::vector<int> gol_grid; 
	// All the available elements that can be spawned
	std::vector<Element*> available_elements;
	// All currently active elements inside the element grid
	std::vector<Element*> active_elements;
	// Elements that need to be added to the active list
	std::vector<Element*> add_queue;
	void mouse_calibrate();
	sf::VertexArray draw_grid(std::vector<Vector> velocities, int cell_size, int  height, int width);
};