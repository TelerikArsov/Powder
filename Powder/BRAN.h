#pragma once
#include "Element.h"
class BRAN :
	public Element
{
public:
	sf::Color states_colors[2];
	int state;
	virtual int update();
	virtual void render(float, float);
	virtual Element* clone() const;
	BRAN();
	~BRAN();
};

