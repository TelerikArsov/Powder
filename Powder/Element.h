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
	int x = 0; // Current position in the grid of elements
	int y = 0; //
	Vector pos = Vector(0, 0);
	Vector velocity;
	double speed;
	Vector terminal_vel_v;
	double terminal_vel;
	Vector forces;
	double drag_coef = 0.6;
	double mass = 100;	   // Not yet used
	int endurance = 0;
	double restitution = 0.6;
	// used by powders in the creation of piles
	// higher values means its harder for pile creation to occure
	// essentially used as velocity threshold
	// at which pile creation will happen
	int pile_threshold = 1; 
	double temperature = 0;
	bool meltable = 0;
	int state = 0; // 0 - liquid 1 - powder 2 - solid 3 - gas 
	Element* low_pressure_transition;		// To which element the current element
	Element* high_pressure_transition;		// will transfrom, based on the current
	Element* low_temperature_transition;	// physical state of the element
	Element* high_temperature_transition;	//
	double low_pressure;                    // Number values at which the 
	double high_pressure;					// transformation will occure
	double low_temperature;
	double high_temperature;
	Vector ground_coll;
	bool collision = false;
	// Moves the element across a line (the start of the line is the 
	// x and y of the element itself and the end is xDestination and yDestination)
	// this function uses a modified version of bresenhams line algorithm
	// return true if there is no collision TODO probably should return
	// the x and y of the cell where collision occurred
	Element* move(Vector dest);
	void calc_loads();
	void update_velocity(double dt);
	void calc_term_vel();
	void set_pos(int x, int y, bool true_pos);
	void powder_pile();
	void apply_impulse(Element* collided_elem, double dt);

	virtual bool update(double dt) = 0;
	virtual void render(double cell_height, double cell_width, sf::Vertex* quad) = 0;
	virtual Element* clone() const = 0;
	virtual ~Element() {};
private:
	Element* move_helper(int xO, int yO, int d, int xStep, int yStep, int de, int dr, bool ytype);
	Element* do_move(int diff_x, int diff_y);
};