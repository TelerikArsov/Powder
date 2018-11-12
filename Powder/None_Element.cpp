#include "None_Element.h"


int None_Element::update()
{
	return 0;
}

void None_Element::render(float cell_height, float cell_width, sf::Vertex * quad)
{
}

Element * None_Element::clone() const
{
	return new None_Element();
}

None_Element::None_Element()
{
	identifier = -1;
}


None_Element::~None_Element()
{
}
