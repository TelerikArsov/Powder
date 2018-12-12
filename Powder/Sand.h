#pragma once
#include "Element.h"
class Sand :
	public Element
{
public:
	bool update() override;
	void render(float, float, sf::Vertex* quad) override;
	Element* clone() const override;
	Sand();
	Sand(const Sand& rhs);
	~Sand();
};

