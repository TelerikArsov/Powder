#pragma once
#include "Element.h"

class None_Element :
	public Element
{
public:
	Element* clone() const;
	None_Element();
	~None_Element();
};

