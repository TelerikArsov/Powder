#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ElementsIds.h"
#include "UI/ElementEditor.h"
#include "Utils/Vector.h"

class Simulation;

class Element
{
public:
	int identifier = -1;
	std::string name = "TMP_ELEMENT";	// Will be used in the ui
	std::string description = "DESC";
	sf::Color color = sf::Color::Blue;	// The main color
	Simulation* sim; // pointer to the Simulation the element currently is 
	ElementEditor* editor = nullptr;
	int menu_id = -1;		// Will be used in the ui 
	int menu_section = -1;	//
	int x = 0; // Current position in the grid of elements
	int y = 0; //
	Vector pos = Vector(0, 0);
	Vector velocity;
	float speed = 0.0f;
	bool moved = false;
	Vector forces;
	float drag_coef = 0.6f;
	float mass = 1;
	int endurance = 0;
	float restitution = 0.6f;
	// used by powders in the creation of piles
	// higher values means its harder for pile creation to occur
	// essentially used as velocity threshold
	// at which pile creation will happen
	int pile_threshold = 1;
	//in kelvins
	float temperature = 0;
	float thermal_cond = 0;
	float specific_heat_cap = 0;
	bool meltable = false;
	int state = 0; // 0 - gas 1 - liquid 2 - powder 3 - solid  
	// Moves the element across a line (the start of the line is the 
	// x and y of the element itself and the end is xDestination and yDestination)
	// this function uses a modified version of bresenhams line algorithm
	// return true if there is no collision 
	Element* move(Vector dest);
	void update_velocity(float dt);
	void set_pos(int x, int y, bool true_pos);
	void apply_collision_impulse(Element* collided_elem, float dt);
	void add_velocity(Vector nvelocity);
	void add_heat(float heat);
	virtual int update(float dt);
	virtual void render(float cell_height, float cell_width, sf::Vertex* quad);
	virtual void draw_ui();
	virtual Element* clone() const = 0;
	virtual ~Element();
protected:
	int low_pressure_transition = -1;		// To which element the current element
	int high_pressure_transition = -1;		// will transfrom, based on the current
	int low_temperature_transition = -1;	// physical state of the element
	int high_temperature_transition = -1;	//
	float low_pressure = -300;                    // Number values at which the 
	float high_pressure = 300;					// transformation will occur
	float low_temperature = -1;
	float high_temperature = 10'000;
	Vector ground_coll;
	Element* collided_elem;
	std::vector<sf::Color> colors;	// All the possible colors
	// 0 - block; the element is blocked from moving further
	// 1 - pass; both elements occupy the same space
	// 2 - swap; the elements switch places
	virtual int eval_col(Element* coll);
	void calc_loads();
	bool collision = false;
	void liquid_move();
	bool powder_pile();
private:
	void move_helper(int xO, int yO, int d, int xStep, int yStep, int de, int dr, bool ytype, Element*& coll_el);
	void do_move(int diff_x, int diff_y, Element*& coll_el);
};