#include "None_Element.h"

Element * None_Element::clone() const
{
	return new None_Element();
}

None_Element::None_Element()
{
	identifier = 0;
}


None_Element::~None_Element()
{
}
