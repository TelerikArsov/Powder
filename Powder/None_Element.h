#pragma once
#include "Element.h"

class None_Element :
	public Element
{
public:
	bool update();
	void render(float cell_height, float cell_width, sf::Vertex* quad);
	Element* clone() const;
	None_Element();
	~None_Element();
};

