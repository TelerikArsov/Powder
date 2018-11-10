#pragma once
#include "Element.h"
class BRAN :
	public Element
{
public:
	sf::Color states_colors[2] = { sf::Color::Blue, sf::Color::White };
	int state;
	int b_rule = 3;
	int s_rule = 3;
	int update();
	void render(float, float, sf::RenderWindow*);
	Element* clone() const;
	BRAN();
	BRAN(const BRAN& rhs);
	~BRAN();
};

