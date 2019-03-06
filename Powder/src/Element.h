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
	sf::Color color = sf::Color::Blue;	// The main color
	Simulation* sim; // pointer to the Simulation the element currently is 
	int menu_id = 0;		// Will be used in the ui 
	int menu_section = 0;	//
	int x = 0; // Current position in the grid of elements
	int y = 0; //
	Vector pos = Vector(0, 0);
	Vector velocity;
	float speed;
	bool moved;
	Vector forces;
	float drag_coef = 0.6f;
	float mass = 1;
	int endurance = 0;
	float restitution = 0.6f;
	// used by powders in the creation of piles
	// higher values means its harder for pile creation to occure
	// essentially used as velocity threshold
	// at which pile creation will happen
	int pile_threshold = 1;
	//in kelvins
	float temperature = 0;
	float thermal_cond = 0;
	float specific_heat_cap = 0;
	bool meltable = false;
	int state = 0; // 0 - gas 1 - liquid 2 - powder 3 - solid  
	Element* low_pressure_transition;		// To which element the current element
	Element* high_pressure_transition;		// will transfrom, based on the current
	Element* low_temperature_transition;	// physical state of the element
	Element* high_temperature_transition;	//
	float low_pressure;                    // Number values at which the 
	float high_pressure;					// transformation will occure
	float low_temperature;
	float high_temperature;
	Vector ground_coll;
	bool collision = false;
	// Moves the element across a line (the start of the line is the 
	// x and y of the element itself and the end is xDestination and yDestination)
	// this function uses a modified version of bresenhams line algorithm
	// return true if there is no collision TODO probably should return
	// the x and y of the cell where collision occurred
	Element* move(Vector dest);
	void calc_loads();
	void update_velocity(float dt);
	void set_pos(int x, int y, bool true_pos);
	bool powder_pile();
	void apply_impulse(Element* collided_elem, float dt);
	void add_velocity(Vector nvelocity);
	void add_heat(float heat);
	virtual bool update(float dt);
	virtual void render(float cell_height, float cell_width, sf::Vertex* quad);
	virtual Element* clone() const = 0;
	virtual ~Element() {};
protected:
	Element* collided_elem;
	std::vector<sf::Color> colors;	// All the possible colors
	// 0 - block; the element is blocked from moving further
	// 1 - pass; both elements occupy the same space
	// 2 - swap; the elements switch places
	virtual int eval_col(Element* coll);
	void liquid_move();
private:
	void move_helper(int xO, int yO, int d, int xStep, int yStep, int de, int dr, bool ytype, Element*& coll_el);
	void do_move(int diff_x, int diff_y, Element*& coll_el);
	bool pile_helper(Vector check_pos);
};