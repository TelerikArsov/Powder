#pragma once
#include "Element.h"
class GOL :
	public Element
{
public:
	sf::Color states_colors[2] = { sf::Color::Blue, sf::Color::White };
	std::string rule_string = "";
	bool rules[3][9] = { false };
	enum { B = 0, S = 1, D = 2 };
	void process_rules();
	int update();
	void render(float, float, sf::Vertex* quad);
	Element* clone() const;
	GOL(int, int, std::string, std::string);
	GOL(const GOL& rhs);
	~GOL();
};

