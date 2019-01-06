#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ElementsIds.h"
#include "Vector.h"

class Simulation;

class Element
{
public:
	int identifier = 0;
	std::string name = "TMP_ELEMENT";	// Will be used in the ui
	std::string description = "DESC";
	sf::Color color = sf::Color::Red;	// The main color(Prob should be an array)
	Simulation* sim; // pointer to the Simulation the element currently is 
	int menu_id = 0;		// Will be used in the ui 
	int menu_section = 0;	//
	int endurance = 0; //
	int x = 0; // Current position in the grid of elements
	int y = 0; //
	Vector pos = Vector(0, 0);
	Vector velocity;
	Vector terminal_vel_v;
	double terminal_vel;
	Vector forces;
	double drag_coef = 1.05;
	double mass = 100;	   // Not yet used
	double temperature = 0;
	bool meltable = 0;
	int state = 0; // 0 - liquid 1 - solid 2 - gas 
	Element* low_pressure_transition;		// To which element the current element 
	Element* high_pressure_transition;		// will transfrom, based on the current
	Element* low_temperature_transition;	// physical state of the element
	Element* high_temperature_transition;	//
	// Moves the element across a line (the start of the line is the 
	// x and y of the element itself and the end is xDestination and yDestination)
	// this function uses a modified version of bresenhams line algorithm
	// return true if there is no collision TODO probably should return
	// the x and y of the cell where collision occurred
	bool move(Vector dest);
	void calc_loads();
	void update_velocity(double dt);
	void calc_term_vel();
	void set_pos(int x, int y);
	virtual bool update(double dt) = 0;
	virtual void render(float cell_height, float cell_width, sf::Vertex* quad) = 0;
	virtual Element* clone() const = 0;
	virtual ~Element() {};
};