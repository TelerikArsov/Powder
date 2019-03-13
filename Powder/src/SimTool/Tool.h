#pragma once 
#include <SFML/Graphics.hpp> 
#include <string>  

class Simulation;

class Tool { 	
public:
	int identifier; 	
	std::string name; 	
	std::string description; 	
	sf::Color color; 	
	virtual void do_action(int x, int y, int element_id = -1, Simulation* sim = nullptr, float strength = 0.0f) = 0;
	virtual ~Tool() {};
};