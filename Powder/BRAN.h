#pragma once
#include "Element.h"
class BRAN :
	public Element
{
public:
	sf::Color states_colors[2] = { sf::Color::Blue, sf::Color::White };
	int b_rule = 3;
	int s_rule = 3;
	int update();
	void render(float, float, sf::Vertex* quad);
	Element* clone() const;
	BRAN(int);
	BRAN(const BRAN& rhs);
	~BRAN();
};

