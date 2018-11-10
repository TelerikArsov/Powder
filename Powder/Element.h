#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Simulation;

class Element
{
public:
	int identifier = 0;
	std::string name = "TMP_ELEMENT";
	std::string description = "DISC";
	sf::Color color = sf::Color::Red;
	Simulation* sim;
	float air_drag = 0.9f;
	int menu_id = 0;
	int menu_section = 0;
	int endurance = 0;
	int corr_x = 0;
	int corr_y = 0;
	float weight = 100;
	float temperature = 0;
	bool meltable = 0;
	int state = 0;
	Element* low_pressure_transition;
	Element* high_pressure_transition;
	Element* low_temperature_transition;
	Element* high_temperature_transition;

	virtual int update() = 0;
	virtual void render(float cell_height, float cell_width, sf::Vertex* quad) = 0;
	virtual Element* clone() const = 0;
	virtual ~Element() {};
};