#pragma once
#include "Element.h"

class None_Element :
	public Element
{
public:
	bool update(double dt) override;
	void render(double cell_height, double cell_width, sf::Vertex* quad) override;
	Element* clone() const;
	None_Element();
	~None_Element();
};

