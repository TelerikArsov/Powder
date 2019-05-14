#pragma once
#include <SFML/Graphics.hpp> 
#include <string>

class SimObject
{
public:
	int identifier = -1;
	std::string name = "SIM_OBJECT";
	std::string description = "DESC";
	sf::Color color = sf::Color::Blue;
	int scrollable_display(bool selected);
	virtual ~SimObject() = 0;
};

